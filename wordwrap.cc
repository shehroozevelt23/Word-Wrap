#include <iostream>
#include <string>
#include <iomanip>
#include <string>
#include <sstream>
using namespace std;

void right(string s, int width)
{
    stringstream ss, spaces;
    int pad = width - s.size();
    for (int i = 0; i < pad; ++i)
        spaces << " ";
    ss << spaces.str() << s;
    cout << ss.str() << endl;
}

void printJustify(string s, int width, string command)
{

    if (command == "-l")
    {
        cout << s << endl;
    }
    else if (command == "-r")
    {
        cout.width(width);
        cout << right << s << endl;
    }
    else if (command == "-c")
    {
        stringstream spaces;
        int gap = width - s.size();
        for (int i = 0; i < gap / 2; ++i)
        {
            spaces << " ";
        }
        cout << spaces.str() << s << endl;
    }
}

void wrap(int width, string command)
{
    string word;
    string output;
    int remaining = width;
    string l;

    while (getline(cin, l))
    {
        stringstream input2(l);
        while (input2 >> word)
        {

            if (word.length() > remaining)
            {
                if (output != "")
                {
                    output = output.substr(0, output.length() - 1);
                    printJustify(output, width, command);
                    remaining = width;

                    output = "";
                    output += word + " ";
                    remaining -= ((word.length()) + 1);
                }

                if (word.length() == width)
                {
                    printJustify(word, width, command);
                    output = "";
                    remaining = width;
                }

                else if (word.length() > width)
                {
                    output = "";
                    output += word + " ";
                    printJustify(word.substr(0, width), width, command);
                    output = "";
                    remaining = width;
                    output += word.substr(width) + " ";
                    remaining -= ((word.substr(width)).length() + 1);
                    while (output.length() > width)
                    {
                        string first_portion = output.substr(0, width);

                        printJustify(first_portion, width, command);
                        output = output.substr(width);
                    }

                    remaining = width - output.length();
                }
                else
                {
                    remaining = width;
                    output = "";
                    output += word + " ";
                    remaining -= (word.length() + 1);
                }
            }
            else if (word.length() == remaining)
            {
                output += word;

                printJustify(output, width, command);

                remaining = width;
                output = "";
            }
            else
            {
                output += word + " ";
                remaining -= (word.length() + 1);
            }
        }
    }
    output = output.substr(0, output.length() - 1);
    printJustify(output, width, command);
}

int main(int argc, char *argv[])
{
    string command = "-l";
    int width = 25;
    istringstream iss;

    for (int i = 1; i < argc; ++i)
    {
        string arg;
        arg = argv[i];
        if (arg == "-w")
        {
            iss.str(argv[i + 1]);
            iss >> width;
        }
        if (arg == "-l" || arg == "-c" || arg == "-r")
        {
            command = argv[i];
            break;
        }
    }

    wrap(width, command);
}