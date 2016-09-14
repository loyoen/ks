default : all
all : ks
ks : main.o CKServer.o CKConfig.o CKMemMgr.o CKPackage.o CKThreadPool.o Thread.o CKReqTaskMgr.o CKIOTaskMgr.o CKTaskMgr.o CTask.o TaskHandler.o KSEpollHandler.o KSEpollCtlBase.o KSLog.o
	g++ -o ks -fstack-protector -fstack-protector-all -g main.o CKServer.o CKConfig.o CKMemMgr.o CKPackage.o CKThreadPool.o Thread.o CKReqTaskMgr.o CKIOTaskMgr.o CKTaskMgr.o CTask.o TaskHandler.o KSEpollHandler.o KSEpollCtlBase.o KSLog.o -lpthread
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
CKThreadPool.o : ./thread/CKThreadPool.cpp ./thread/CKThreadPool.h ./thread/Thread.h ./config/CKConfig.h ./tasks/TaskHandler.h
	g++ -c ./thread/CKThreadPool.cpp
Thread.o : ./thread/Thread.cpp ./thread/Thread.h
	g++ -c ./thread/Thread.cpp
CKReqTaskMgr.o : ./tasks/CKReqTaskMgr.cpp ./tasks/CKReqTaskMgr.h ./tasks/CKTaskMgr.h
	g++ -c ./tasks/CKReqTaskMgr.cpp
CKIOTaskMgr.o : ./tasks/CKIOTaskMgr.cpp ./tasks/CKIOTaskMgr.h ./tasks/CKTaskMgr.h ./thread/Thread.h
	g++ -c ./tasks/CKIOTaskMgr.cpp	
CKTaskMgr.o : ./tasks/CKTaskMgr.cpp ./tasks/CKTaskMgr.h ./tasks/CTask.h ./epoll/KSEpollCtlBase.h
	g++ -c ./tasks/CKTaskMgr.cpp
CTask.o : ./tasks/CTask.cpp ./tasks/CTask.h ./memory/CKPackage.h
	g++ -c ./tasks/CTask.cpp
TaskHandler.o : ./tasks/TaskHandler.cpp ./tasks/TaskHandler.h ./tasks/CKTaskMgr.h
	g++ -c ./tasks/TaskHandler.cpp
KSEpollHandler.o : ./epoll/KSEpollHandler.cpp ./epoll/KSEpollHandler.h ./config/CKConfig.h ./thread/Thread.h ./epoll/KSEpollCtlBase.h
	g++ -c ./epoll/KSEpollHandler.cpp
KSEpollCtlBase.o : ./epoll/KSEpollCtlBase.cpp ./epoll/KSEpollCtlBase.h
	g++ -c ./epoll/KSEpollCtlBase.cpp
KSLog.o : ./log/KSLog.cpp ./log/KSLog.h ./tasks/CKIOTaskMgr.h
	g++ -c ./log/KSLog.cpp

clean :
	rm -f ks *.o
