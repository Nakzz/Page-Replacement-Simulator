#include "argparser.h"

SpecNode *argParser(int argc, char **argv)
{
    SpecNode *specifications = initSpecNode();
    if (argc > 6)
    {
        errorReport("TOO MANY ARGUMENTS");
    }

    int opt;
    while ((opt = getopt(argc, argv, "-:p:m:")) != -1)
    {

        switch (opt)
        {

        case 'p':
            if (optarg != 0x0)
            {
                if (optarg[0] - '-' == 0)
                {
                    if (isAllDigit(optarg))
                    {
                        errorReport("NEGATIVE PAGE SIZE SPECIFIED");
                    }
                    else
                    {
                        errorReport("NON NUMERICAL PAGE SIZE SPECIFIED");
                    }
                }
                if (!(isAllDigit(optarg)))
                {
                    errorReport("NON NUMERICAL PAGE SIZE SPECIFIED");
                }
                unsigned long num = strtoul(optarg, NULL, 10);
                if (isPowerOfTwo(num))
                {
                    specifications->pageSize = num;
                }
                else
                {
                    errorReport("PAGE SIZE SPECIFIED IS NOT POWER OF 2");
                }
            }
            else
            {
                errorReport("INVALID PAGE SIZE SPECIFIED");
            }
            break;
        case 'm':
            if (optarg != 0x0)
            {
                if (optarg[0] - '-' == 0)
                {
                    errorReport("NEGATIVE REAL MEMORY SIZE SPECIFIED");
                }
                if (!(isAllDigit(optarg)))
                {
                    errorReport("NON NUMERICAL REAL MEMORY SIZE SPECIFIED");
                }
                unsigned long num = strtoul(optarg, NULL, 10);
                num = num * 1048576;
                specifications->memSize = num;
            }
            else
            {
                errorReport("INVALID PAGE NUMBER SPECIFIED");
            }
            break;
        case ':':
            printf("Missing arg for %c\n", optopt);
            exit(-1);
            break;
        default:
            specifications->traceFile = optarg;
        }
    }
    return specifications;
}

SpecNode *initSpecNode()
{
    SpecNode *specifications = malloc(sizeof(SpecNode));
    if (specifications == NULL)
    {
        errorReport("BAD MALLOC OR UNABLE TO MALLOC");
    }
    specifications->memSize = 1048576;
    specifications->pageSize = 4096;
    return specifications;
}
bool isPowerOfTwo(unsigned long n)
{
    if (n == 0)
        return false;

    return (ceil(log2(n)) == floor(log2(n)));
}