default : all
all : ks
ks : main.o CKServer.o CKConfig.o CKMemMgr.o CKPackage.o CKThreadPool.o Thread.o CKTaskMgr.o CTask.o KSEpollHandler.o
	g++ -o ks main.o CKServer.o CKConfig.o CKMemMgr.o CKPackage.o CKThreadPool.o Thread.o CKTaskMgr.o CTask.o KSEpollHandler.o -lpthread
main.o : main.cpp CKServer.h
	g++ -c main.cpp
CKServer.o : CKServer.cpp CKServer.h ./config/CKConfig.h ./memory/CKMemMgr.h ./thread/CKThreadPool.h ./tasks/CKTaskMgr.h
	g++ -c CKServer.cpp
CKConfig.o : ./config/CKConfig.cpp ./config/CKConfig.h
	g++ -c ./config/CKConfig.cpp
CKMemMgr.o : ./memory/CKMemMgr.cpp ./memory/CKMemMgr.h ./config/CKConfig.h ./memory/CKPackage.h 
	g++ -c ./memory/CKMemMgr.cpp
CKPackage.o : ./memory/CKPackage.cpp ./memory/CKPackage.h
	g++ -c ./memory/CKPackage.cpp
CKThreadPool.o : ./thread/CKThreadPool.cpp ./thread/CKThreadPool.h ./thread/Thread.h ./config/CKConfig.h
	g++ -c ./thread/CKThreadPool.cpp
Thread.o : ./thread/Thread.cpp ./thread/Thread.h
	g++ -c ./thread/Thread.cpp
CKTaskMgr.o : ./tasks/CKTaskMgr.cpp ./tasks/CKTaskMgr.h ./tasks/CTask.h
	g++ -c ./tasks/CKTaskMgr.cpp
CTask.o : ./tasks/CTask.cpp ./tasks/CTask.h ./memory/CKPackage.h
	g++ -c ./tasks/CTask.cpp
KSEpollHandler.o : ./epoll/KSEpollHandler.cpp ./epoll/KSEpollHandler.h ./config/CKConfig.h ./thread/Thread.h
	g++ -c ./epoll/KSEpollHandler.cpp
