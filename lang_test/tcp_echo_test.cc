
#include <stdlib.h>

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>

#include "tsdl/lang/context.h"
#include "tsdl/lang/program_node.h"
#include "tsdl/lang/init_node.h"
#include "tsdl/lang/executor.h"
#include "tsdl/lang/condition_checker.h"

#include <boost/asio.hpp>
using namespace boost::asio;

class InitExecutor : public Executor {
    virtual Result* execute(std::string inputParam) {
        ::system("sh stop_server.sh");
        return NULL;
    }
};
class SetupExecutor : public Executor {
    virtual Result* execute(std::string inputParam) {
        ::system("sh run_server.sh");
        return NULL;

    }
};
class TeardownExecutor : public Executor {
    virtual Result* execute(std::string inputParam) {
        ::system("sh stop_server.sh");
        return NULL;

    }
};

class EchoResult : public Result {
public:
    EchoResult(std::string ret) : _ret(ret) {
        this->_result = this;
    }
    virtual ~EchoResult() {}

    std::string _ret;
};

class EchoClientExecutor : public Executor {
    virtual Result* execute(std::string inputParam) {

        if( inputParam.empty() ) {
            throw ExecuteException("input parameter empty. \"");
        }

        io_service io;
        ip::tcp::iostream s("127.0.0.1", "30000");

        std::cout << "Client->Server : " << inputParam << std::endl;
        s << inputParam << std::endl;
        s.flush();

        sleep(1);

        std::string str;
        getline(s, str);

        std::cout << "Server->Client : " << str << std::endl;
        return new EchoResult(str);

    }
};

class TestExecuteFactory : public ExecutorFactory {
    typedef std::map<std::string, int> RegistMap;
public:
    TestExecuteFactory() 
    {
        _nameMap.insert(std::make_pair("init", 1));
        _nameMap.insert(std::make_pair("setup", 2));
        _nameMap.insert(std::make_pair("teardown", 3));
        _nameMap.insert(std::make_pair("Echo", 4));
    }
    virtual Executor* create(std::string name)
    {
        RegistMap::iterator ite = _nameMap.find(name);
        switch (ite->second) {
            case 1:
                return new InitExecutor();
            case 2:
                return new SetupExecutor();
            case 3:
                return new TeardownExecutor();
            case 4:
                return new EchoClientExecutor();

        }
        return NULL;
    }
private:
    RegistMap _nameMap;
};

class EchoResultChecker : public ConditionChecker {
public:
    virtual bool check(Result* result, std::string input) {
        EchoResult* ret = result->getResult<EchoResult*>();
        if(ret->_ret == input) {
            return true;
        }

        _error = "expected = [" + input + "]" + " but was = [" + ret->_ret + "]";
        return false;
    }

    virtual std::string getError() const {
        return _error;;
    }
protected:
    std::string _error;
};
class TypeAChecker : public ConditionChecker {
public:
    virtual bool check(Result* result, std::string input) {
        std::cout << "TypeAChecker check end. input = " << input << std::endl;
        return true;
    }
};
class TypeBChecker : public ConditionChecker {
public:
    virtual bool check(Result* result, std::string input) {
        std::cout << "TypeBChecker check end. input = " << input << std::endl;
        return true;
    }
};
class TestConditionCheckerFactory : public ConditionCheckerFactory {
    typedef std::map<std::string, int> RegistMap;
public:
    TestConditionCheckerFactory() 
    {
        _nameMap.insert(std::make_pair("EchoCheck", 1));
    }
    virtual ConditionChecker* create(std::string name)
    {
        RegistMap::iterator ite = _nameMap.find(name);
        switch (ite->second) {
            case 1:
                return new EchoResultChecker();
        }
        return NULL;
    }
private:
    RegistMap _nameMap;
};

int main(int argc, char const* argv[])
{

    std::ifstream* ifs = NULL;
    if(argc == 2) {
        if(strcmp(argv[1], "-interactive") == 0) {
            assert(false);
            //ifs = new std::istream(std::cin.rdbuf());
        }
    } else {
        ifs = new  std::ifstream("echo_test_script.txt");
    }

    Context c(ifs);

    ProgramNode p;
    try {
        p.parse(c);
        p.setExecutorFactory(new TestExecuteFactory());
        p.setConditionCheckerFactory(new TestConditionCheckerFactory());
        p.execute();
    } catch (ParseException& e) {
        std::cout << e.what() << std::endl;
    } catch (ExecuteException& e) {
        std::cout << e.what() << std::endl;
    }
    delete ifs;

    return 0;
}
