# TSDL
## Author
    Youhei.Sekiguchi <ysekiguchi.zzz@gmail.com>

## Require
### Build
  * cmake version 2.6 or later.

### Library
  * boost Library (date_time)

----
# Description of Software
This software is test tool for integration test. Test scenario is described with simple script.
TSDL is test framework. so, you must define behavior for test.

follow:
 * init : Cleanup for running of test target
 * setup : Test target run.
 * Executor :  Operating for a test.
 * ConditionChecker : the condition check after operation. It can connect by "and"
 * teardown : Test target halt.
 
{{{
init <input string>
setup <input string> : cond ConditionChecker <input string>
execute Executor : cond ConditionChecker <input string> and cond .....
teardown <input string> : cond null
}}}

## Getting Started


## features
 * Test reporting
  * Supported plain test format and JUnit format.
  * Measure the elapsed time of the test.
 * Test configration
  * you can change the test target by the config file at the anytime.
  * you can switch on or off by the config file.

