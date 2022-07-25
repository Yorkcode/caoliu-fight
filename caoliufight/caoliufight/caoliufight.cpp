#include <iostream>
#include <stdio.h>
#include<graphics.h>
#include <conio.h>
#include<vector>
using namespace std;
constexpr auto swidth = 1500;
constexpr auto sheight = swidth / 16 * 9;
constexpr auto speed = 50;
constexpr unsigned int hp = 3;
constexpr auto hurttime = 1000;//伤害冷却
bool PointInRect(int x, int y, RECT& r)
{

    return (r.left <= x && x <= r.right && r.top <= y && r.bottom >= y);
}
bool RectCrashRect(RECT& r1, RECT& r2)
{
    RECT r;
    r.left = r1.left - (r2.right - r2.left);
    r.right = r1.right;
    r.top = r1.top - (r2.bottom - r2.top);
    r.bottom = r1.bottom;




    return(r.left < r2.left&& r2.left < r.right&& r.top < r2.top&& r2.top < r.bottom);
}
void Welcome()
{
    LPCTSTR title = _T("三国大战");
    LPCTSTR tplay = _T("开始");
    LPCTSTR texit = _T("退出");

    RECT tplayr, texitr;
    BeginBatchDraw();
    setbkcolor(WHITE);
    cleardevice();
    settextstyle(100, 0, _T("黑体"));
    settextcolor(BLACK);

    outtextxy(swidth / 2 - textwidth(title) / 2, sheight / 10, title);

    settextstyle(70, 0, _T("黑体"));

    tplayr.left = swidth / 2 - textwidth(tplay) / 2;
    tplayr.right = tplayr.left + textwidth(tplay);
    tplayr.top = sheight / 5 * 2;
    tplayr.bottom = tplayr.top + textheight(tplay);


    texitr.left = swidth / 2 - textwidth(texit) / 2;
    texitr.right = texitr.left + textwidth(texit);
    texitr.top = sheight / 5 * 3;
    texitr.bottom = texitr.top + textheight(texit);

    outtextxy(tplayr.left, tplayr.top, tplay);

    outtextxy(texitr.left, texitr.top, texit);

    EndBatchDraw();



    while (true)
    {
        ExMessage mess;
        getmessage(&mess, EM_MOUSE);
        if (mess.lbutton)
        {
            if (PointInRect(mess.x, mess.y, tplayr))
            {
                return;
            }
            else if (PointInRect(mess.x, mess.y, texitr))
            {
                exit(0);

            }

        }

    }


}
void Over(unsigned long long& kill)
{
    TCHAR* str = new TCHAR[128];
    _stprintf_s(str, 128, _T("击杀曹军数量:%llu"), kill);
    settextcolor(RED);
    outtextxy(swidth / 2 - textwidth(str) / 2, sheight / 5, str);
    //按回车返回

    LPCTSTR info = _T("按回车返回");
    settextstyle(20, 0, _T("黑体"));
    outtextxy(swidth - textwidth(info), sheight - textheight(info), info);
    while (true)
    {
        ExMessage mess;
        getmessage(&mess, EM_KEY);
        if (mess.vkcode == 0x0D)
        {
            return;
        }
    }


}
//各种类 背景
class BK
{
public:
    BK(IMAGE& img)
        :img(img)
    {

    }
    void Show()
    {

        putimage(0, 0, &img);//定义X,Y坐标
    }
private:
    IMAGE& img;


};
class Hero1
{
public:
    Hero1(IMAGE& img)
        :img(img)
    {
        rect.left = 0;
        rect.top = 0;
        rect.right = img.getwidth();
        rect.bottom = img.getheight();

    }
    void Show()
    {


        putimage(rect.left, rect.top, &img);

    }
    void Control()
    {
        ExMessage mess;
        if (peekmessage(&mess, EM_MOUSE))
        {
            rect.left = mess.x - img.getwidth() / 2;
            rect.top = mess.y - img.getheight() / 2;
            rect.right = rect.left + img.getwidth();
            rect.bottom = rect.top + img.getheight();

        }
    }

private:
    IMAGE& img;
    RECT rect;//人物矩形边框


};
class Hero2//用#include <conio.h>和_getch()
{
public:
    Hero2(IMAGE& img)
        :img(img)
    {
        rect.left = 0;
        rect.top = 0;
        rect.right = img.getwidth();
        rect.bottom = img.getheight();
    }
    void Show()
    {


        putimage(rect.left, rect.top, &img);

    }
    void Control()
    {

        /*ExMessage mess;
        if (peekmessage(&mess, EM_KEY))
        {
            switch ((int)mess.vkcode)
            {

            case VK_LEFT:
                rect.left -= speed;
                rect.right -= speed;
                break;
            case VK_RIGHT:
                rect.top -= speed;
                rect.bottom -= speed;
                break;
            case VK_UP:
                rect.left += speed;
                rect.right += speed;
                break;
            case VK_DOWN:
                rect.top += speed;
                rect.bottom += speed;
                break;
            default:
                break;
            }
*/

        char key = _getch();
        switch (key)
        {
        case 72:  //↑
        case 119: //w
            rect.top -= speed;
            rect.bottom -= speed;
            break;
        case 80:  //↓
        case 115: //s
            rect.top += speed;
            rect.bottom += speed;
            break;
        case 75: //←
        case 97: //a
            rect.left -= speed;
            rect.right -= speed;
            break;
        case 77:  //→
        case 100: //d
            rect.left += speed;
            rect.right += speed;
            break;

        case 27://Esc直接退出
            exit(0);
            break;
        }







    }
private:
    IMAGE& img;
    RECT rect;//人物矩形边框
};//22222222//
//键盘操控
class Hero3//
{
public:
    Hero3(IMAGE& img)
        :img(img)
    {
        rect.left = 0;
        rect.top = 0;
        rect.right = img.getwidth();
        rect.bottom = img.getheight();
    }
    void Show()
    {


        putimage(rect.left, rect.top, &img);

    }
    void Control()
    {

        ExMessage mess;
        if (peekmessage(&mess, EM_KEY))
        {
            switch ((int)mess.message)
            {
            case WM_KEYDOWN:
            {
                if ((int)mess.vkcode == 37)
                {
                    rect.left -= speed;
                    rect.right -= speed;
                }
                else if ((int)mess.vkcode == 38)
                {
                    rect.top -= speed;
                    rect.bottom -= speed;
                }
                else if ((int)mess.vkcode == 39)
                {
                    rect.left += speed;
                    rect.right += speed;
                }
                else if ((int)mess.vkcode == 40)
                {
                    rect.top += speed;
                    rect.bottom += speed;
                }
            }
            break;
            }
            /*
        case 37:
            rect.left -= speed;
            rect.right -= speed;
            break;
        case 38:
            rect.top -= speed;
            rect.bottom -= speed;
            break;
        case 39:
            rect.left += speed;
            rect.right += speed;
            break;
        case 40:
            rect.top += speed;
            rect.bottom += speed;
            break;
        case 27:
            exit(0);
        ;
        }
        */

            if (rect.left > swidth || rect.top > sheight || rect.bottom < 0 || rect.right < 0)
            {
                rect.left = 0;
                rect.top = 0;
                rect.right = img.getwidth();
                rect.bottom = img.getheight();
            }






        }
    }

private:
    IMAGE& img;
    RECT rect;//人物矩形边框
};//键盘操控
//鼠标操控
class Hero
{
public:
    Hero(IMAGE& img)
        :img(img), HP(hp)
    {
        rect.left = swidth / 2 - img.getwidth() / 2;
        rect.top = sheight / 2 - img.getheight() / 2;
        rect.right = rect.left + img.getwidth();
        rect.bottom = sheight;

    }
    void Show()
    {
        setlinecolor(RED);//显示血条
        setlinestyle(PS_SOLID, 4);
        putimage(rect.left, rect.top, &img);
        line(rect.left, rect.top - 5, rect.left + (img.getwidth() / hp * HP), rect.top - 5);

    }
    void Control()
    {
        ExMessage mess;
        if (peekmessage(&mess, EM_MOUSE))
        {
            rect.left = mess.x - img.getwidth() / 2;
            rect.top = mess.y - img.getheight() / 2;
            rect.right = rect.left + img.getwidth();
            rect.bottom = rect.top + img.getheight();

        }


    }
    bool hurt()
    {
        HP--;
        return (HP == 0) ? false : true;
    }
    RECT& GetRect()
    {
        return rect;
    }

private:
    IMAGE& img;
    RECT rect;//人物矩形边框
    unsigned int HP;

};
class Army
{
public:
    Army(IMAGE& img, int x, IMAGE*& boom)
        :img(img), isdie(false), boomsum(0)
    {
        selfboom[0] = boom[0];
        selfboom[1] = boom[1];
        rect.left = x;
        rect.right = rect.left + img.getwidth();
        rect.top = -img.getheight();
        rect.bottom = 0;
    }
    bool Show()
    {
        if (isdie)
        {
            if (boomsum == 10)
            {
                return false;
            }
            putimage(rect.left, rect.top, selfboom - boomsum / 5);
            boomsum++;
            return true;
        }


        if (rect.top >= sheight)
        {
            return false;
        }
        rect.top += 2;
        rect.bottom += 2;
        putimage(rect.left, rect.top, &img);
        return true;
    }


    RECT& GetRect()
    {
        return rect;
    }
    void Isdie()
    {
        isdie = true;
    }
private:
    IMAGE& img;
    RECT rect;
    IMAGE selfboom[2];
    bool isdie;
    int boomsum;

};

class Mymen
{
public:
    Mymen(IMAGE& img, RECT pr)
        :img(img)
    {
        rect.left = pr.left + (pr.right - pr.left) / 2 - img.getwidth() / 2;
        rect.right = rect.left + img.getwidth();
        rect.top = pr.top - img.getheight();
        rect.bottom = rect.top + img.getheight();
    }
    bool Show()
    {
        if (rect.bottom <= 0)
        {
            return false;
        }
        rect.top -= 3;
        rect.bottom -= 3;
        putimage(rect.left, rect.top, &img);
        return true;
    }
    RECT& GetRect()
    {
        return rect;
    }

protected://继承,为了实现曹军和汉军的区别
    IMAGE& img;
    RECT rect;
};
class Mymenn :public Mymen
{
public:
    Mymenn(IMAGE& img, RECT pr)
        :Mymen(img, pr)
    {
        rect.left = pr.left + (pr.right - pr.left) / 2 - img.getwidth() / 2;
        rect.right = rect.left + img.getwidth();
        rect.top = pr.bottom;
        rect.bottom = rect.top + img.getheight();

    }
    bool Show()
    {
        if (rect.top >= sheight)
        {
            return false;
        }
        rect.top += 4;
        rect.bottom += 4;
        putimage(rect.left, rect.top, &img);
        return true;
    }
    RECT& GetRect()
    {
        return rect;
    }

private:


};




bool AddArmy(vector<Army*>& es, IMAGE& armyimg, IMAGE* boom)
{

    Army* e = new Army(armyimg, abs(rand()) % (swidth - armyimg.getwidth()), boom);

    for (auto& i : es)//遍历
    {
        if (RectCrashRect(i->GetRect(), e->GetRect()))
        {
            delete e;
            return false;
        }
    }
    es.push_back(e);
    return true;



}


bool Play()
{
    setbkcolor(WHITE);
    cleardevice();
    bool is_play = true;
    IMAGE meimg, mapimg, armyimg, Mymenimg, caocaomenimg;
    IMAGE boomimg[2];
    loadimage(&meimg, _T("D:\\C++\\caoliufight\\me2.png"));
    loadimage(&mapimg, _T("D:\\C++\\caoliufight\\map3.png"), swidth, sheight);
    loadimage(&armyimg, _T("D:\\C++\\caoliufight\\caocao.png"));
    loadimage(&Mymenimg, _T("D:\\C++\\caoliufight\\Mymen1.jpg"));
    loadimage(&caocaomenimg, _T("D:\\C++\\caoliufight\\army11.jpg"));
    loadimage(&boomimg[0], _T("D:\\C++\\caoliufight\\boom1.png"));
    loadimage(&boomimg[1], _T("D:\\C++\\caoliufight\\boom2.png"));
    BK bk = BK(mapimg);
    Hero me = Hero(meimg);

    vector<Army*>es;
    vector<Mymen*>ms;
    vector<Mymenn*>mns;
    clock_t hurtlast = clock();

    int bsing = 0;
    unsigned long long kill = 0;

    for (int i = 0; i < 2; i++)
    {
        AddArmy(es, armyimg, boomimg);


    }



    while (is_play)
    {
        bsing++;
        if (bsing % 30 == 0)//出现的频率  汉军
        {

            ms.push_back(new Mymen(Mymenimg, me.GetRect()));

        }


        if (bsing == 100)//出现的频率 曹军
        {
            bsing = 0;
            //汉军

            for (auto& i : es)
            {
                mns.push_back(new Mymenn(caocaomenimg, i->GetRect()));
            }
        }



        BeginBatchDraw();

        bk.Show();
        Sleep(2);
        //flushmessage();
        //Sleep(2);
        me.Control();
        //暂停功能
        ExMessage mess;
        if (_kbhit())
        {
            char v = _getch();
            if (v == 0x20)
            {
                Sleep(500);
                while (true)
                {
                    if (_kbhit())
                    {
                        v = _getch();
                        if (v == 0x20)
                        {
                            break;
                        }
                    }
                    Sleep(10);
                }

            }
        }
        //

        me.Show();
        //Sleep(16);

        //生成并且销毁汉军
        auto i2t = ms.begin();
        while (i2t != ms.end())
        {
            if (!(*i2t)->Show())
            {
                i2t = ms.erase(i2t);
            }
            else
            {
                i2t++;

            }

        }
        //
        //生成并且销毁曹军
        auto i3t = mns.begin();
        while (i3t != mns.end())
        {

            if (!(*i3t)->Show())
            {
                i3t = mns.erase(i3t);
            }

            else
            {
                if (RectCrashRect((*i3t)->GetRect(), me.GetRect()))
                {
                    if (clock() - hurtlast >= hurttime)
                    {
                        is_play = me.hurt();
                        hurtlast = clock();
                    }


                }
                i3t++;

            }


        }
        //

        auto it = es.begin();//敌人遍历
        while (it != es.end())//敌人与自己人遍历
        {
            if (RectCrashRect((*it)->GetRect(), me.GetRect()))//
            {
                if (clock() - hurtlast >= hurttime)
                {
                    is_play = me.hurt();
                    hurtlast = clock();
                }

                break;
            }
            auto mit = ms.begin();
            while (mit != ms.end())
            {
                if (RectCrashRect((*mit)->GetRect(), (*it)->GetRect()))
                {
                    //销毁敌人
                    (*it)->Isdie();



                    //销毁自己人
                    delete(*mit);
                    ms.erase(mit);//
                    kill++;//击杀数

                    break;//自己人已经无了 跳出循环
                }
                mit++;
            }
            if (!(*it)->Show())
            {
                //销毁敌人
                delete(*it);
                es.erase(it);
                it = es.begin();//
            }
            it++;
        }
        for (int i = 0; i < 5 - es.size(); i++)//避免死循环 设置小于等于5个
        {
            AddArmy(es, armyimg, boomimg);
        }

        EndBatchDraw();


    }

    Over(kill);
    return true;

}



int main()

{
    initgraph(swidth, sheight, EW_NOMINIMIZE | EW_SHOWCONSOLE);
    bool is_live = true;
    while (is_live)
    {
        Welcome();
        //play
        is_live = Play();



    }



    return 0;
}

