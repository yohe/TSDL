
#include <iostream>
#include <assert.h>
#include "tsdl/scenario.h"
#include "tsdl/outputter.h"

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
        assert( tree.insert("/", new ScenarioCase("aaaa.scn", "test2", NULL), error) );
        ScenarioCase tmp_1("aaaa.scn", "test5", NULL);
        assert( tree.insert("/test2", &tmp_1, error) == false );
        //std::cout << error << std::endl;
        assert( error == "test2 isn't group.");
        assert( tree.insert("/test1", new ScenarioGroup("test3"), error) );
        assert( tree.insert("/test1/test3/", new ScenarioCase("aaaa.scn", "test4", NULL ), error) );
        ScenarioCase tmp_2("aaaa.scn", "test6", NULL );
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
        ScenarioManager manager(NULL, NULL, "./scenario.conf");

        assert(manager.setup());
        assert(manager.getError() == "");

        const ScenarioTree& tree = manager.getScenarioTree();

        assert( manager.addScenario("/test2", "aaaa.scn") );
        assert( tree.find("/test2") != NULL);
        assert( manager.addGroup("/test1") );
        assert( manager.addScenario("/test1/test3", "aaaaa.scn") );
        assert( manager.addScenario("/test1/test4", "aaaaa.scn") );
        assert( tree.find("/test1/test3") != NULL);

        assert( manager.addScenario("/test2", "aaaa.scn") == false );
        assert( manager.addGroup("/test1") == false );

        TextOutputter outputter("test.result");
        XmlOutputter xml_outputter("test.result.xml");
        ScenarioResultCollector collector;
        manager.run(&outputter, &collector);

        collector.output(&xml_outputter);

        assert( manager.delScenario("/test3") == false);
        assert( manager.delScenario("/test2") );

        assert( manager.delGroup("/test1") == false);
        assert( manager.delScenario("/test1/test3") );
        assert( manager.delScenario("/test2") == false);
        assert( manager.delGroup("/test1", true) );

        assert( manager.addGroup("/test1") );
        assert( manager.addScenario("/test1/test3", "aaaaa.scn") );
        assert( manager.addScenario("/test1/test4", "aaaaa.scn") );
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
        ScenarioCase* test1 = new ScenarioCase("aaaa.scn", "test1", &root);
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
        collector.output(&outputter);
    }

    return 0;
}

