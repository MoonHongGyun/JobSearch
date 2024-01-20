#include <iostream>
#include "Job.h"
#include <vector>

using std::cout;
using std::endl;
int main()
{
    int detailnum, infonum;
    Start start;
    User user;
    while (1)
    {
        switch (start.FirstMap())
        {
        case 1:
            user.SignUp();
            break;
        default:
            if (user.Login() == 1)
            {
                switch (start.MainMap(user.Division()))
                {
                case 1:
                    start.SearchMap();
                    detailnum = start.SearchMap2();
                    if (detailnum != 0)
                        infonum = start.DetailMap(detailnum);
                    start.Cinfo(infonum);
                    break;
                case 3:
                    start.CoUpdate();
                default:
                    break;
                }
            }
            break;
        }
    }
}
