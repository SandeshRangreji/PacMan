#include<fstream>
#include<iostream>
#include<string.h>

using namespace std;

int main()
{
    fstream f;

    f.open("level.dat",ios::binary| ios::out);

    struct level
    {
        char thegrid[32][29]={"wwwwwwwwwwwwwwwwwwwwwwwwwwww",         //the grid is stored as a char array. w:wall `.':pellet `*':power pellet
                              "wA....H.....BwwA.....H....Bw",
                              "w.wwww.wwwww.ww.wwwww.wwww.w",
                              "w*wwww.wwwww.ww.wwwww.wwww*w",
                              "w.wwww.wwwww.ww.wwwww.wwww.w",
                              "wC....H..H..H..H..H..H....Dw",
                              "wwwwww.ww.wwwwwwww.ww.wwwwww",
                              "     w.ww.wwwwwwww.ww.w     ",
                              "     w.wwC..BwwA..Dww.w     ",
                              "     w.wwwww ww wwwww.w     ",
                              "     w.wwwww ww wwwww.w     ",
                              "     w.wwa  huvh  bww.w     ",
                              "     w.ww www==www ww.w     ",
                              "wwwwww.ww w      w ww.wwwwww",
                              "wq    H  hw      wh  H    pw",
                              "wwwwww.ww w12dc34w ww.wwwwww",
                              "     w.ww wwwwwwww ww.w     ",
                              "     w.wwh        hww.w     ",
                              "     w.ww wwwwwwww ww.w     ",
                              "wwwwww.ww wwwwwwww ww.wwwwww",
                              "wA....H..H..BwwA..H..H....Bw",
                              "w.wwww.wwwww.ww.wwwww.wwww.w",
                              "w.wwww.wwwww.ww.wwwww.wwww.w",
                              "wC*BwwH..H..Ho H..H..HwwA*Dw",
                              "www.ww.ww.wwwwwwww.ww.ww.www",
                              "www.ww.ww.wwwwwwww.ww.ww.www",
                              "wA.H..DwwC..BwwA..DwwC..H.Bw",
                              "w.wwwwwwwwww.ww.wwwwwwwwww.w",
                              "w.wwwwwwwwww.ww.wwwwwwwwww.w",
                              "wC..........H..H..........Dw",
                              "wwwwwwwwwwwwwwwwwwwwwwwwwwww"  };
    }saver;




    f.write((char*)&saver, sizeof(saver));

    strcpy(saver.thegrid[0],"wwwwwwwwwwwwwwwwwwwwwwwwwwww");
    strcpy(saver.thegrid[1],"wA....H.....H..H.....H....Bw");
    strcpy(saver.thegrid[2],"w.wwww.wwwww.ww.wwwww.wwww.w");
    strcpy(saver.thegrid[3],"wH..H.H...H.H..H.H...H.H..Hw");
    strcpy(saver.thegrid[4],"w.ww.wwwww.wwwwww.wwwww.ww.w");
    strcpy(saver.thegrid[5],"w.wADwwwwwH.H..H.HwwwwwCBw.w");
    strcpy(saver.thegrid[6],"w.w.wwA...Dw.ww.wC...Bww.w.w");
    strcpy(saver.thegrid[7],"w.w.ww.wwwww.ww.wwwww.ww.w.w");
    strcpy(saver.thegrid[8],"w.w.wwH h v h  h u h Hww.w.w");
    strcpy(saver.thegrid[9],"wH.H..Dw w=wwwwww=w wC..H.Hw");
    strcpy(saver.thegrid[10],"w.w.wwww w==wwww==w wwww.w.w");
    strcpy(saver.thegrid[11],"w.w.wwww w   ww   w wwwwH.Dw");
    strcpy(saver.thegrid[12],"w.w.wwww wc34ww12dw wwww.www");
    strcpy(saver.thegrid[13],"w.wH*...HwwwwwwwwwwH....HHpw");
    strcpy(saver.thegrid[14],"w.w.wwwwH..BwwwwA..Hwwwww.ww");
    strcpy(saver.thegrid[15],"wC.H.Bww.ww.wwww.wwH.....Dww");
    strcpy(saver.thegrid[16],"wwwww.ww.wwH.H..Hww.wwwwwwww");
    strcpy(saver.thegrid[17],"wq.H.HH.Hww.w.ww.wwH.H.*Bwww");
    strcpy(saver.thegrid[18],"www.ww.w.ww.wCBw.ww.w.ww.www");
    strcpy(saver.thegrid[19],"wA.Hww.wC..Hww.wH..Dw.wwH.Bw");
    strcpy(saver.thegrid[20],"w.w.ww.wwww.wADw.wwww.ww.w.w");
    strcpy(saver.thegrid[21],"wC.Hww.wwww.w.ww.wwww.wwH.Dw");
    strcpy(saver.thegrid[22],"wwwH..H....HwCBwH....H..Hwww");
    strcpy(saver.thegrid[23],"www.wwwwwww.ww.w.wwwwwww.www");
    strcpy(saver.thegrid[24],"www.wwwwwwwH..H.Hwwwwwww.www");
    strcpy(saver.thegrid[25],"wwAH.......HwwwwH.......HBww");
    strcpy(saver.thegrid[26],"ww.wwwwwwwwH.o..Hwwwwwwww.ww");
    strcpy(saver.thegrid[27],"wADwwwwwwww.wwww.wwwwwwwwCBw");
    strcpy(saver.thegrid[28],"w.wA.BwA.BwH....HwA.BwA.Bw.w");
    strcpy(saver.thegrid[29],"wC.DwC.DwC.DwwwwC.DwC.DwC.Dw");
    strcpy(saver.thegrid[30],"wwwwwwwwwwwwwwwwwwwwwwwwwwww");

    f.write((char*)&saver, sizeof(saver));

    strcpy(saver.thegrid[0],"wwwwwwwwwwwwwwwwwwwwwwwwwwww");
    strcpy(saver.thegrid[1],"wA........H.BwwA.H........Bw");
    strcpy(saver.thegrid[2],"w.wwwwwwww w.ww.w.wwwwwwww.w");
    strcpy(saver.thegrid[3],"w.wA......Hw.ww.wH......Bw.w");
    strcpy(saver.thegrid[4],"w.w.wwwwww.w.ww.w.wwwwww.w.w");
    strcpy(saver.thegrid[5],"w.wC....H.Dw.ww.wC.H....Dw.w");
    strcpy(saver.thegrid[6],"w.wwwwww.www.ww.www.wwwwww.w");
    strcpy(saver.thegrid[7],"wH Bwwww.www.ww.www.wwwwA.Hw");
    strcpy(saver.thegrid[8],"w.wH....Hwww.ww.wwwH....Hw.w");
    strcpy(saver.thegrid[9],"w.w.wwww.www.ww.www.wwww.w.w");
    strcpy(saver.thegrid[10],"w.w.wwww.wA.HwwH.Bw.wwww.w.w");
    strcpy(saver.thegrid[11],"w.w.wwww.w.w.ww.w.w.wwww.w.w");
    strcpy(saver.thegrid[12],"w.wH  u H.Dw.ww.wC.H v  Hw.w");
    strcpy(saver.thegrid[13],"w.w ww=w www.ww.www w=ww w.w");
    strcpy(saver.thegrid[14],"wH Hww w www.ww.www w wwH Hw");
    strcpy(saver.thegrid[15],"w.w ww wH pw.ww.wq Hw ww w.w");
    strcpy(saver.thegrid[16],"w.w w2dw www.ww.www wc3w w.w");
    strcpy(saver.thegrid[17],"w.w wwww www.ww.www wwww w.w");
    strcpy(saver.thegrid[18],"w.wH....H.Bw.ww.wA.H....Hw.w");
    strcpy(saver.thegrid[19],"w.w.wwwwww.w.ww.w.wwwwww.w.w");
    strcpy(saver.thegrid[20],"w.w.wwwwww.w.ww.w.wwwwww.w.w");
    strcpy(saver.thegrid[21],"w.w.wwwwww.w.ww.w.wwwwww.w.w");
    strcpy(saver.thegrid[22],"wH.H...H.uDw.ww.wCu.H...H Hw");
    strcpy(saver.thegrid[23],"w.w.www.w=ww.ww.ww=w.www.w.w");
    strcpy(saver.thegrid[24],"w.wC.Bw.w  w.ww.w  w.wA.Dw.w");
    strcpy(saver.thegrid[25],"w.www.w.wc4w.ww.w1dw.w.www.w");
    strcpy(saver.thegrid[26],"wH...Hw.wwww.ww.wwww.wH...Hw");
    strcpy(saver.thegrid[27],"w.wwwC.H..Bw.ww.wA..H.Dwww.w");
    strcpy(saver.thegrid[28],"w.wwwwwwww w.wwow.wwwwwwww.w");
    strcpy(saver.thegrid[29],"wC........H.DwwC H........Dw");
    strcpy(saver.thegrid[30],"wwwwwwwwwwwwwwwwwwwwwwwwwwww");

     f.write((char*)&saver, sizeof(saver));

     strcpy(saver.thegrid[0],"wwwwwwwwwwwwwwwwwwwwwwwwwwww");
    strcpy(saver.thegrid[1],"wA.H.H.H.H.H*..*H.H.H.H.H.Bw");
    strcpy(saver.thegrid[2],"w.w.w.w.w.w.wwww.w.w.w.w.w w");
    strcpy(saver.thegrid[3],"wH.H.H.H.H.H....H.H.H.H.H.Hw");
    strcpy(saver.thegrid[4],"w.w.w.w.w.w.wwww.w.w.w.w.w.w");
    strcpy(saver.thegrid[5],"wH.H.H.H.H.H....H.H.H.H.H.Hw");
    strcpy(saver.thegrid[6],"w.w.w.w.w.w.wwww.w.w.w.w.w.w");
    strcpy(saver.thegrid[7],"wH.H.H.H.H.H....H.H.H.H.H.Hw");
    strcpy(saver.thegrid[8],"w.w.w.w.w.w.wwww.w.w.w.w.w.w");
    strcpy(saver.thegrid[9],"wH.H.H.H.H.H....H.H.H.H.H.Hw");
    strcpy(saver.thegrid[10],"w.w.w.w.w.w.wwww.w.w.w.w.w.w");
    strcpy(saver.thegrid[11],"wH.H.H.H.H.H*uv*H.H.H.H.H.Hw");
    strcpy(saver.thegrid[12],"w.w.w.w.w.www==www.w.w.w.w.w");
    strcpy(saver.thegrid[13],"w.w.w.w.w.w12dc34w.w.w.w.w.w");
    strcpy(saver.thegrid[14],"w.w.w.w.w.wwwwwwww.w.w.w.w.w");
    strcpy(saver.thegrid[15],"wH.H.H.H.H.H....H.H.H.H.H.Hw");
    strcpy(saver.thegrid[16],"w.w.w.w.w.w.wwww.w.w.w.w.w.w");
    strcpy(saver.thegrid[17],"wH.H.H.H.H.H....H.H.H.H.H.Hw");
    strcpy(saver.thegrid[18],"w.w.w.w.w.w.wwww.w.w.w.w.w.w");
    strcpy(saver.thegrid[19],"wH.H.H.H.H.H....H.H.H.H.H.Hw");
    strcpy(saver.thegrid[20],"w.w.w.w.w.w.wwww.w.w.w.w.w.w");
    strcpy(saver.thegrid[21],"wH.H.H.H.H.H....H.H.H.H.H.Hw");
    strcpy(saver.thegrid[22],"w.w.w.w.w.w.wwww w.w.w.w.w.w");
    strcpy(saver.thegrid[23],"wH.H.H.H.H.H o  H.H.H.H.H.Hw");
    strcpy(saver.thegrid[24],"w.w.w.w.w.w.wwww.w.w.w.w.w.w");
    strcpy(saver.thegrid[25],"wH.H.H.H.H.H....H.H.H.H.H.Hw");
    strcpy(saver.thegrid[26],"w.w.w.w.w.w.wwww.w.w.w.w.w.w");
    strcpy(saver.thegrid[27],"wH.H.H.H.H.H....H.H.H.H.H.Hw");
    strcpy(saver.thegrid[28],"w.w.w.w.w.w.wwww.w.w.w.w.w.w");
    strcpy(saver.thegrid[29],"wC.H.H.H.H.H*..*H.H.H.H.H.Dw");
    strcpy(saver.thegrid[30],"wwwwwwwwwwwwwwwwwwwwwwwwwwww");

    f.write((char*)&saver, sizeof(saver));

    strcpy(saver.thegrid[0],"                            ");
    strcpy(saver.thegrid[1],"                            ");
    strcpy(saver.thegrid[2],"                            ");
    strcpy(saver.thegrid[3]," wwwwwwwwwww                ");
    strcpy(saver.thegrid[4]," wA..*....Bw                ");
    strcpy(saver.thegrid[5]," w.wwwwwww.w                ");
    strcpy(saver.thegrid[6],"ww.wwww  w.w                ");
    strcpy(saver.thegrid[7],"wAH  pw  w.w                ");
    strcpy(saver.thegrid[8],"w.wwwww  w.w                ");
    strcpy(saver.thegrid[9],"w.w      w.w                ");
    strcpy(saver.thegrid[10],"w.wwwwwwww.wwwwwwwwwwwwwwwww");
    strcpy(saver.thegrid[11],"wH........H......H........Bw");
    strcpy(saver.thegrid[12],"w.wwwwwwww.wwwwww.wwwwwwww.w");
    strcpy(saver.thegrid[13],"w.w      w.w    w.w      w.w");
    strcpy(saver.thegrid[14],"w.w      w.w    w.w      w.w");
    strcpy(saver.thegrid[15],"w.wwwwwwww.wwwwww.wwwwwwww.w");
    strcpy(saver.thegrid[16],"wcu  H....H.H..H.H....H  vdw");
    strcpy(saver.thegrid[17],"ww=ww.wwwwww.ww.wwwwww.ww=ww");
    strcpy(saver.thegrid[18],"w   w.wa  bw.ww.wa  bw.w   w");
    strcpy(saver.thegrid[19],"w   w.w ww w.ww.w ww w.w   w");
    strcpy(saver.thegrid[20],"w2d w.wc4 dw.ww.wc 3dw.w1d w");
    strcpy(saver.thegrid[21],"wwwww.wwwwww.ww.wwwwww.wwwww");
    strcpy(saver.thegrid[22],"wwwwwC......H oH.H....H...Hw");
    strcpy(saver.thegrid[23],"wwwwwwwwwwwwwwwww.wwwwwwww.w");
    strcpy(saver.thegrid[24],"                w.w      w.w");
    strcpy(saver.thegrid[25],"                w.w  wwwww.w");
    strcpy(saver.thegrid[26],"                w.w  wq  HDw");
    strcpy(saver.thegrid[27],"                w.w  wwww.ww");
    strcpy(saver.thegrid[28],"                w.wwwwwww.w ");
    strcpy(saver.thegrid[29],"                wC....*..Dw ");
    strcpy(saver.thegrid[30],"                wwwwwwwwwww ");

     f.write((char*)&saver, sizeof(saver));





    f.close();






}
