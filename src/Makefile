#makefile to test interface (to be deleted)
 
CXX=g++
CXXFLAGS=-O2 -Wall -pedantic -lpanel -lncurses
interface:	Interface.o ChatWindow.o ContactList.o InputField.o InterfaceIndicator.o
		$(CXX) -o interface ChatWindow.o ContactList.o InputField.o InterfaceIndicator.o Interface.o $(CXXFLAGS)
Interface.o:	Interface.cpp Interface.hpp
		$(CXX) -o Interface.o -c Interface.cpp $(CXXFLAGS)
ChatWindow.o: ChatWindow.cpp ChatWindow.hpp
		$(CXX) -o ChatWindow.o -c ChatWindow.cpp $(CXXFLAGS)
ContactList.o: ContactList.cpp ContactList.hpp
		$(CXX) -o ContactList.o -c ContactList.cpp $(CXXFLAGS)
InputField.o: InputField.cpp InputField.hpp
		$(CXX) -o InputField.o -c InputField.cpp $(CXXFLAGS)
InterfaceIndicator.o: InterfaceIndicator.cpp InterfaceIndicator.hpp
		$(CXX) -o InterfaceIndicator.o -c InterfaceIndicator.cpp $(CXXFLAGS)
clean:
		rm -f *.o
