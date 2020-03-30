import sys
sys.path.append("F:\Atom Projects")

import grpc
import test_pb2
import test_pb2_grpc

filename = input("Please enter the File's Name: ")
f = open(filename, "r")
content = f.read()
f.close()

with grpc.insecure_channel('localhost:50051') as channel:
    stub = test_pb2_grpc.GreetingStub(channel)
    response = stub.SayHello(test_pb2.HelloRequest(name='you'))
    response3 = stub.SendFile(test_pb2.File(fileName=filename, fileContent=content))

print("Greeter client received: " + response.message)
print("Greeter client received: " + response3.message)
