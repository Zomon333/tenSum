/*
Copyright 2022 Dagan Poulin
   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at
       http://www.apache.org/licenses/LICENSE-2.0
   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>

using namespace std;

//----------------------------------
// Formatting & Helper functions
//----------------------------------

//Generates a single pair.
int generatePair(int pair)
{
    return 10-pair;
}

//Formats the results to the desired notation
string formatResult(int pair)
{
    return "["+to_string(pair)+","+to_string(generatePair(pair))+"]";
}

//Shows the help menu as if -h or --help were called.
void showHelp()
{
        cout<<"The tenPair command takes an integer array as a parameter, and outputs all of the pairs that sum up to 10."<<endl;
        cout<<"The tenPair command has 3 modes of execution in order to determine which flags to keep"<<endl;
        cout<<endl;
        cout<<"Usage:"<<endl;
        cout<<endl;
        cout<<"tenPair <flags> <parameters>"<<endl;
        cout<<endl;
        cout<<"Examplel:"<<endl;
        cout<<endl;
        cout<<"./tenpair -a 1 1 2 4 4 5 5 6 7 9"<<endl;
        cout<<endl;
        cout<<endl<<"Flags:"<<endl;
        cout<<endl;
        cout<<"-h               Alias to --help."<<endl;
        cout<<"--help           Displays this help command."<<endl;
        cout<<"-a               Alias to --all."<<endl;
        cout<<"--all            Outputs all pairs."<<endl;
        cout<<"-o               Alias to --ordered."<<endl;
        cout<<"--ordered        Outputs all unique ordered pairs."<<endl;
        cout<<"-u               Alias to --unordered"<<endl;
        cout<<"--unordered      Outputs all unique unordered pairs."<<endl;
}



//----------------------------------
// Generation functions
//----------------------------------

//Generate all unique unordered pairs. Duplicates removed, reverses kept.
void generateUnordered(vector<int> pairU)
{
    unordered_map<int, bool> hasPrinted(false);
    unordered_map<int, int> counts(0);

    //Count how many of each number there are
    for(int i = 0; i<=pairU.size(); i++)
    {
        counts[pairU[i]]=1;
    }

    //Then, for each section:
    for(int i = 0; i<pairU.size(); i++)
    {
        counts[pairU[i]] *= counts[generatePair(pairU[i])];
        if(counts[pairU[i]]>0 && !hasPrinted[pairU[i]])
        {
            cout<<formatResult(pairU[i]);
            hasPrinted[pairU[i]]=true;
        }
    }

}

//Generate all unique ordered pairs. Duplicates and reverses removed.
void generateOrdered(vector<int> pairO)
{
    unordered_map<int, bool> hasPrinted(false);
    unordered_map<int, int> counts(0);

    //Count how many of each number there are
    for(int i = 0; i<=pairO.size(); i++)
    {
        counts[pairO[i]]=1;
    }

    //Then, for each section:
    for(int i = 0; i<pairO.size(); i++)
    {
        counts[pairO[i]] *= counts[generatePair(pairO[i])];
        if(counts[pairO[i]]>0 && !hasPrinted[pairO[i]])
        {
            cout<<formatResult(pairO[i]);
            hasPrinted[pairO[i]]=true;
            hasPrinted[generatePair(pairO[i])]=true;
        }
    }

}

//Generates all pairs with no regard for output. Includes duplicates and reverse order.
void generateAll(vector<int> pairA)
{
    unordered_map<int, bool> hasPrinted(false);
    unordered_map<int, int> counts(0);

    //Count how many of each number there are
    for(int i = 0; i<=pairA.size(); i++)
    {
        counts[pairA[i]]++;
    }

    //Then, for each section:
    for(int i = 0; i<=pairA.size(); i++)
    {
        //If that value hasn't already printed, begin printing it and mark it as printed.
        if(!hasPrinted[pairA[i]])
        {
            if(pairA[i]!=5)
            {
                //Print the value the number of times it's supposed to exist
                for(int j = 0; j<counts[pairA[i]]*counts[generatePair(pairA[i])]; j++)
                {
                    cout<<"["<<to_string(pairA[i])<<","<<to_string(generatePair(pairA[i]))<<"]";
                }
            }
            else
            {
                //Print the value the number of times it's supposed to exist
                for(int j = 0; j<((counts[pairA[i]])*(counts[pairA[i]]-1)); j++)
                {
                    cout<<"["<<to_string(pairA[i])<<","<<to_string(generatePair(pairA[i]))<<"]";
                }
            }
            hasPrinted[pairA[i]]=true;
        }
    }

}




//----------------------------------
// Main driver
//----------------------------------
int main(int argc, char* argv[])
{
    
    // Parameter and flag checks
    //----------------------------------


    //Check and see if there are any parameters or if flag is specified
    if(argc<2)
    {
        cout<<"Invalid flags."<<endl;
        showHelp();
        return -1;
    }

    //If there are parameters, there should be a flag. Pull out that flag.
    string flag = argv[1];

    //Help flag
    if(flag=="-h" || flag=="--help")
    {
        showHelp();
        return 0;
    }

    //Check to see if there's exactly two parameters, but they're not -h.
    if(argc==2)
    {
        cout<<"Invalid parameters. See --help for more info.\n";
        return -1;
    }

    //Check for all other flags. If it isn't one of these, then it's an incorrect command.
    if(flag!="-a" && flag!="--all" && flag!="-o" && flag!="--ordered" && flag!="-u" && flag!="--unordered")
    {
        cout<<"Invalid flags."<<endl;
        showHelp();
        return -1;
    }

 
    // Vector Initialization
    //----------------------------------
    vector<string> strArgs(argv+2, argv+argc);
    vector<int> intArgs = vector<int>(strArgs.size());

    for(int i = 0; i < strArgs.size(); i++)
    {
        intArgs[i] = stoi(strArgs[i]);
    }



    // Flag Select for -a, -o, -u
    //----------------------------------

    //Flag for All
    if(flag=="-a" || flag=="--all")
    {
        generateAll(intArgs);
        cout<<endl;
        return 1;
    }

    //Flag for Ordered Pairs
    if(flag=="-o" || flag=="--ordered")
    {
        generateOrdered(intArgs);
        cout<<endl;
        return 1;
    }

    //Flag for Unordered Pairs
    if(flag=="-u" || flag=="--unordered")
    {
        generateUnordered(intArgs);
        cout<<endl;
        return 1;
    }

    //If the program reaches here, there's been an error.
    return -1;

}
