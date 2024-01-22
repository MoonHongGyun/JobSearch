#include <iostream>
#include "Job.h"
#include <vector>

using std::cout;
using std::endl;
int main()
{
    int detailnum, infonum, back = 0, search;
    Start start;
    User user;
    while (1)
    {
        switch (start.FirstMap())
        {
        case 1:
            user.SignUp();
            break;
        case 2:
            if (user.Login() == 1)
            {
                back = 0;
                while (back == 0)
                {
                    switch (start.MainMap(user.Division()))
                    {
                    case 1:
                        search = start.SearchMap();
                        while (1)
                        {
                            detailnum = start.SearchMap2(search);
                            if (detailnum != 0)
                            {
                                while (1)
                                {
                                    infonum = start.DetailMap(detailnum);
                                    if (infonum == 0)
                                        break;
                                    start.Cinfo(infonum);
                                }
                            }
                            else
                                break;
                        }
                        break;
                    case 2:
                        back = 1;
                        break;
                    case 3:
                        start.CoUpdate();
                        break;
                    default:
                        break;
                    }
                }
            }
            break;
        default:
            exit(1);
        }
    }
}
