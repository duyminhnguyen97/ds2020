import sys
sys.path.append("F:\Atom Projects")

import test_pb2_grpc
import test_pb2
import grpc
from concurrent import futures
import numpy as np

f = open("server.txt", "r")
data = f.read()
f.close()

class Greeting(test_pb2_grpc.GreetingServicer):

    def SayHello(self, request, context):
        return test_pb2.HelloReply(message='Hello, %s!' % request.name)

    def SayHelloAgain(self, request, context):
        return test_pb2.HelloReply(message='Hello again, %s!' % request.name)

    def SendFile(self, request, context):
        filename = request.fileName
        f = open(filename, "w")
        f.write(request.fileContent)
        f.close()
        return test_pb2.HelloReply(message="The server have received your file: %s" % request.fileName)


server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
test_pb2_grpc.add_GreetingServicer_to_server(Greeting(), server)

print('Starting server. Listening on port 50051.')
server.add_insecure_port('[::]:50051')
server.start()
server.wait_for_termination()
