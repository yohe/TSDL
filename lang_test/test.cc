
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

class InitExecutor : public Executor {
    virtual Result* execute(std::string inputParam) {
        std::cout << "init execute. input = " << inputParam << std::endl;
        return NULL;
    }
};
class SetupExecutor : public Executor {
    virtual Result* execute(std::string inputParam) {
        std::cout << "setup execute. input = " << inputParam << std::endl;
        return NULL;

    }
};
class TeardownExecutor : public Executor {
    virtual Result* execute(std::string inputParam) {
        std::cout << "teardown execute. input = " << inputParam << std::endl;
        return NULL;

    }
};

class FizzBuzzResult : public Result {
public:
    FizzBuzzResult(int fizz, int buzz, int fizzbuzz) : fizzCount(fizz), buzzCount(buzz), fizzbuzzCount(fizzbuzz) {
        this->_result = this;
    }
    virtual ~FizzBuzzResult() {}


    int fizzCount;
    int buzzCount;
    int fizzbuzzCount;
};

class FizzBuzzExecutor : public Executor {
    virtual Result* execute(std::string inputParam) {
        std::string low = inputParam.substr(0, inputParam.find("-"));
        std::string high = inputParam.substr(inputParam.find("-")+1);
        std::stringstream ss;
        ss << low << " " << high;
        int lowValue = 0;
        int highValue = 0;
        ss >> lowValue;
        ss >> highValue;
        if( lowValue == 0 || highValue == 0 || lowValue >= highValue) {
            throw ExecuteException("input parameter error. input format is \"LowNumber-HighNumber\"");
        }

        int fizzCount = 0;
        int buzzCount = 0;
        int fizzbuzzCount = 0;
        for(int i = lowValue; i <= highValue; ++i) {
            if( i % 3 == 0 && i % 5 == 0 && i % 15 == 0) {
                std::cout << "FizzBuzz ";
                fizzbuzzCount++;
            } else if( i % 5 == 0 ) {
                std::cout << "Buzz ";
                buzzCount++;
            } else if( i % 3 == 0 ) {
                std::cout << "Fizz ";
                fizzCount++;
            } else
                std::cout << i << " ";

        }

        std::cout << std::endl;

        return new FizzBuzzResult(fizzCount, buzzCount, fizzbuzzCount);

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
        _nameMap.insert(std::make_pair("FizzBuzz", 4));
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
                return new FizzBuzzExecutor();

        }
        return NULL;
    }
private:
    RegistMap _nameMap;
};

class FizzBuzzChecker : public ConditionChecker {
public:
    virtual bool check(Result* result, std::string input) {
        FizzBuzzResult* ret = result->getResult<FizzBuzzResult*>();
        std::string type = input.substr(0, input.find("-"));
        std::string count = input.substr(input.find("-")+1);
        std::stringstream ss;
        ss << count;
        int countValue = 0;
        ss >> countValue;

        if(type == "Fizz") {
            if(ret->fizzCount == countValue) {
                return true;
            } else {
                std::stringstream ss;
                ss << "fizz : expected = [" << countValue << "] but was = [" << ret->fizzCount << "]";
                _error = ss.str();
                return false;
            }
        } else if( type == "Buzz") {
            if(ret->buzzCount == countValue) {
                return true;
            } else {
                std::stringstream ss;
                ss << "buzz : expected = [" << countValue << "] but was = [" << ret->buzzCount << "]";
                _error = ss.str();
                return false;
            }
        } else if (type == "FizzBuzz") {
            if(ret->fizzbuzzCount == countValue) {
                return true;
            } else {
                std::stringstream ss;
                ss << "fizzbuzz : expected = [" << countValue << "] but was = [" << ret->fizzbuzzCount << "]";
                _error = ss.str();
                return false;
            }
        }

        return false;
    }

    virtual std::string getError() const {
        return _error;
    }

private:
    std::string _error;
};
class TypeAChecker : public ConditionChecker {
public:
    virtual bool check(Result* result, std::string input) {
        std::cout << "TypeAChecker check end. input = " << input << std::endl;
        return true;
    }

    virtual std::string getError() const {
        return "null";
    }

};
class TypeBChecker : public ConditionChecker {
public:
    virtual bool check(Result* result, std::string input) {
        std::cout << "TypeBChecker check end. input = " << input << std::endl;
        return true;
    }
    virtual std::string getError() const {
        return "null";
    }
};
class TestConditionCheckerFactory : public ConditionCheckerFactory {
    typedef std::map<std::string, int> RegistMap;
public:
    TestConditionCheckerFactory() 
    {
        _nameMap.insert(std::make_pair("FizzBuzzCheck", 3));
        _nameMap.insert(std::make_pair("TypeA", 4));
        _nameMap.insert(std::make_pair("TypeB", 5));
    }
    virtual ConditionChecker* create(std::string name)
    {
        RegistMap::iterator ite = _nameMap.find(name);
        switch (ite->second) {
            case 3:
                return new FizzBuzzChecker();
            case 4:
                return new TypeAChecker();
            case 5:
                return new TypeBChecker();

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
        ifs = new  std::ifstream("test_script.txt");
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
