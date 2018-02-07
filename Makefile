test:myShell.cpp analyse.cpp analyse.h makePathVector.cpp makePathVector.h search.cpp search.h startRun.cpp startRun.h cd.cpp cd.h interpretVar.cpp interpretVar.h setVar.cpp setVar.h exportVar.cpp exportVar.h
	g++ -o test -std=gnu++98 -Wall -Werror myShell.cpp analyse.cpp makePathVector.cpp search.cpp startRun.cpp cd.cpp interpretVar.cpp setVar.cpp exportVar.cpp
clean:
	rm -f *~ test
