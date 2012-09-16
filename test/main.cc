
#include <iostream>
#include <assert.h>
#include "tsdl/lang.h"
#include "tsdl/scenario.h"
#include "tsdl/outputter.h"

class TestScenarioCase : public ScenarioCase {
public:
    TestScenarioCase(const std::string& scenario_file, const std::string& name, ScenarioEntry* parent = NULL) :
        ScenarioCase(scenario_file, name, parent) {}

    virtual ~TestScenarioCase() {}

protected:
    virtual ProgramNode* createProgramNode() const {
        return new ProgramNode();
    }

};

class TestScenarioManager : public ScenarioManager {
public:
    TestScenarioManager(ExecutorFactory* exeFactory, ConditionCheckerFactory* condFactory, const std::string& config = "") :
        ScenarioManager(exeFactory, condFactory, config) {}

protected:
    virtual ScenarioCase* createScenarioCase(const std::string& scenario_file, const std::string& name, ScenarioEntry* parent = NULL) {
        return new TestScenarioCase(scenario_file, name, parent);
    }


};

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
        sleep(1);

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

class TestConditionCheckerFactory : public ConditionCheckerFactory {
    typedef std::map<std::string, int> RegistMap;
public:
    TestConditionCheckerFactory() 
    {
        _nameMap.insert(std::make_pair("FizzBuzzCheck", 3));
    }
    virtual ConditionChecker* create(std::string name)
    {
        RegistMap::iterator ite = _nameMap.find(name);
        switch (ite->second) {
            case 3:
                return new FizzBuzzChecker();
        }
        return NULL;
    }
private:
    RegistMap _nameMap;
};


int main(int argc, char const* argv[])
{
    
    std::cout  << "---------------ScenarioTree Test------------------" << std::endl;
    {
        std::string error;
        ScenarioTree tree;
        assert( tree.insert("/", new ScenarioGroup("test1"), error) );
        ScenarioGroup tmp_3("test1");
        assert( tree.insert("/", &tmp_3, error) == false );
        //std::cout << error << std::endl;
        assert( error == "test1 is already exist.");
        assert( tree.insert("/", new TestScenarioCase("aaaa.scn", "test2", NULL), error) );
        TestScenarioCase tmp_1("aaaa.scn", "test5", NULL);
        assert( tree.insert("/test2", &tmp_1, error) == false );
        //std::cout << error << std::endl;
        assert( error == "test2 isn't group.");
        assert( tree.insert("/test1", new ScenarioGroup("test3"), error) );
        assert( tree.insert("/test1/test3/", new TestScenarioCase("aaaa.scn", "test4", NULL ), error) );
        TestScenarioCase tmp_2("aaaa.scn", "test6", NULL );
        assert( tree.insert("/test1/test3/test5/test6", &tmp_2, error) == false);
        //std::cout << error << std::endl;
        assert( error == "/test1/test3/test5/test6 isn't exist.");

        assert( tree.find("/") != NULL );
        assert( tree.find("/test1/test3") != NULL);
        assert( tree.find("/test1/test3/test4") != NULL);
        assert( tree.find("/test1/test3/test5") == NULL);

        assert( tree.erase("/test2", false, error) );                // ScenarioCase remove.
        assert( tree.erase("/test3", false, error) == false );       // Entry don't exist
        //std::cout << error << std::endl;
        assert( error == "/test3 isn't exsit.");
        assert( tree.erase("/test1/test3", false, error) == false);
        //std::cout << error << std::endl;
        assert( error == "test3 has children yet.");
        assert( tree.erase("/test1/test3", true, error) );    // children(test4) exists yet. but remove by force flag.
        assert( tree.erase("/test1", false, error) );                // ScearioGroup remove.

    }


    std::cout  << "---------------ScenarioManager Test------------------" << std::endl;
    {
        TestScenarioManager manager(new TestExecuteFactory(), new TestConditionCheckerFactory(), "./scenario.conf");

        assert(manager.setup());
        assert(manager.getError() == "");

        const ScenarioTree& tree = manager.getScenarioTree();

        assert( manager.addGroup("/test2") );
        assert( tree.find("/test2") != NULL);
        assert( manager.addGroup("/test1") );
        assert( manager.addScenario("/test1/test3", "test.scn") );
        assert( manager.addScenario("/test1/test4", "test.scn") );
        assert( tree.find("/test1/test3") != NULL);

        assert( manager.addScenario("/test2/test5", "test.scn") );
        assert( manager.addScenario("/test2", "aaaa.scn") == false );
        assert( manager.addGroup("/test1") == false );

        TextOutputter outputter("test.result");
        JUnitOutputter junit_outputter("test.result_junit.xml");
        ScenarioResultCollector collector;
        manager.run(&outputter, &collector);

        collector.output(&junit_outputter, 0, 0, 0);

        assert( manager.delScenario("/test3") == false);
        assert( manager.delScenario("/test2/test5") );
        assert( manager.delGroup("/test2") );

        assert( manager.delGroup("/test1") == false);
        assert( manager.delScenario("/test1/test3") );
        assert( manager.delScenario("/test2") == false);
        assert( manager.delGroup("/test1", true) );

        assert( manager.addGroup("/test1") );
        assert( manager.addScenario("/test1/test3", "test.scn") );
        assert( manager.addScenario("/test1/test4", "test.scn") );
        assert( manager.addGroup("/test2") );
        assert( manager.moveScenario("/test1/test3", "/test2/test3") );
        assert( tree.find("/test2/test3") != NULL);
        assert( tree.find("/test1/test3") == NULL);


        assert( manager.moveGroup("/test1", "/test2/test1") );
        assert( tree.find("/test2/test1/test4") != NULL);

    }

    std::cout << "-----------------ScenarioResultCollector Test---------------------" << std::endl;
    {
        ScenarioGroup root("", NULL);
        ScenarioCase* test1 = new TestScenarioCase("aaaa.scn", "test1", &root);
        //std::cout << test1.fullpath() << std::endl;
        assert( test1->fullpath() == "/test1");
        //std::cout << root.fullpath() << std::endl;
        assert( root.fullpath() == "/");
        root.add(test1);
        ScenarioResultCollector collector(&root);
        ScenarioResult* result = new ScenarioResult("/", "", true);
        ScenarioResult* result1 = new ScenarioResult("/test1", "test1", false, "ERROR");
        collector.addResult("/", result);
        collector.addResult("/test1", result1);
        TextOutputter outputter("test2.result");
        collector.output(&outputter, 0, 0, 0);
    }


    std::cout << "-----------------Timer Test---------------------" << std::endl;
    {
        using namespace boost::posix_time;
        Timer t;
        std::cout << "t.now() toString -->" << t.now() << std::endl;

        std::cout << "     ## CountUpTimer Test" << std::endl;
        CountUpTimer cut;
        cut.set();
        sleep(1);
        assert(cut.elapsed().total_seconds() == 1);
        cut.set();
        assert(cut.pause().total_milliseconds() == 0);
        assert(cut.isPause());
        sleep(1);
        assert(cut.elapsed().total_seconds() == 0);
        assert(cut.pause().total_seconds() == 1);
        assert(cut.elapsed().total_seconds() == 0);
        sleep(1);
        assert(cut.elapsed().total_seconds() == 1);
        std::cout << "cut.elapsed() toString --> " << to_simple_string(cut.elapsed()) << std::endl;

        std::cout << "     ## CountDownTimer Test" << std::endl;
        CountDownTimer cdt;
        cdt.set(2000);
        cdt.pause();
        assert(cdt.remainingTime() <= 2000);
        assert(cdt.isTimeOver() == false);
        assert(cdt.isPause() == true);
        cdt.pause();
        assert(cdt.isPause() == false);
        sleep(1);
        assert(cdt.remainingTime() <= 1000);
        assert(cdt.isTimeOver() == false);
        sleep(1);
        assert(cdt.remainingTime() == 0);
        assert(cdt.isTimeOver() == true);
    }

    return 0;
}

