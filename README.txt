Project structure
    \BillingSystem          - billing module
    \BillingSystem.Tests    - unit tests
    \Additions              - unit tests framework
    
    
OS supported:
    - Windows;
    - Linux;
    
    
Dependencies:
    - Perl or Python for UnitTests(CxxTest);
    
    
How to run application:
    - Windows(Visual Studio):
    - Open BillingSystem\BillingSystem\BillingSystem.vcxproj
    - Press "Run"
    
    Linux:
    - Run command "make BillingSystem" from location "BillingSystem\BillingSystem\src\Makefile"
    - Run "./BillingSystem"

    
How to run untiTests:
    Windows(Visual Studio):
    - Open BillingSystem\BillingSystem.Tests\BillingSystem.Tests.vcxproj;
    - Press "Build";
    - In Output will be printed results;
    
    Linux:
    - Run command "make libBillingSystem" from location "BillingSystem\BillingSystem\src\Makefile". It makes library for tests.
    - Run command "./BuildTests.sh" from location "BillingSystem\BillingSystem.Tests"
    - Run "./BillingSystemTest"
    
    
Configuration:
    - All config files located in "BillingSystem\BillingSystem\data";
    - BillingSettings.csv - contain billing values such as cost;
    - IncomingLog.csv - log for processing via Billing module;
    - IncomingAccountsInfo.csv - existed accounts and them settings;
    - OutcomingAccountsInfo.csv - will be generated automatically with Account values after played IncomingLog.csv;
    