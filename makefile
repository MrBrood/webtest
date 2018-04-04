
BOOST_DIR=/usr/lib64/libboost_system-mt.so.1.53.0
#BOOST_SYSTEM=$(BOOST_DIR) + "libbost_system-mt.so.1.53.0"
all:
	echo $(BOOST_DIR)
	g++ -g main_web.cpp $(BOOST_DIR) -std=c++0x -o main_web
