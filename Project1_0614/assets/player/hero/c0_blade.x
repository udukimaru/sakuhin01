xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 66;
 -0.62664;0.03318;0.05395;,
 -0.15772;0.28574;0.12255;,
 -0.39519;0.76424;0.12187;,
 -0.85057;0.50304;0.03740;,
 -0.62664;0.03318;0.05395;,
 0.60133;-2.11177;0.15042;,
 0.98686;-1.88430;0.22454;,
 -0.15772;0.28574;0.12255;,
 0.60133;-2.11177;0.15042;,
 1.38929;-3.86082;0.26293;,
 1.86483;-3.57319;0.31069;,
 0.98686;-1.88430;0.22454;,
 1.38929;-3.86082;0.26293;,
 2.56967;-4.85164;0.26880;,
 1.86483;-3.57319;0.31069;,
 2.31751;-3.40233;0.19377;,
 2.31751;-3.40233;0.19377;,
 1.35524;-1.72938;0.09230;,
 1.35524;-1.72938;0.09230;,
 0.32763;0.54663;0.00306;,
 0.32763;0.54663;0.00306;,
 0.04550;0.97690;-0.02711;,
 -0.62664;0.03318;0.05395;,
 -0.17210;0.29430;-0.15001;,
 0.96756;-1.96086;-0.00605;,
 0.60133;-2.11177;0.15042;,
 0.96756;-1.96086;-0.00605;,
 1.84778;-3.61718;0.09991;,
 1.38929;-3.86082;0.26293;,
 0.60133;-2.11177;0.15042;,
 1.84778;-3.61718;0.09991;,
 2.56967;-4.85164;0.26880;,
 1.38929;-3.86082;0.26293;,
 2.31751;-3.40233;0.19377;,
 1.35524;-1.72938;0.09230;,
 2.31751;-3.40233;0.19377;,
 0.32763;0.54663;0.00306;,
 1.35524;-1.72938;0.09230;,
 -0.17210;0.29430;-0.15001;,
 -0.39356;0.74851;-0.16200;,
 0.04550;0.97690;-0.02711;,
 0.32763;0.54663;0.00306;,
 -0.62664;0.03318;0.05395;,
 -0.85057;0.50304;0.03740;,
 0.39549;2.10512;-0.11506;,
 -0.25862;1.20487;0.18432;,
 -0.85549;0.87049;0.22196;,
 -1.96962;0.80439;0.05085;,
 -0.59358;1.35243;0.04474;,
 -1.35082;2.82628;-0.04098;,
 -1.51633;2.72941;-0.02941;,
 -0.80664;1.23982;0.07231;,
 -1.52846;2.71396;-0.21416;,
 -0.80157;1.23612;-0.12298;,
 -1.34546;2.78031;-0.22250;,
 -0.59600;1.34010;-0.15815;,
 -0.26819;1.19666;-0.29396;,
 -0.88017;0.87136;-0.24654;,
 -1.35392;2.95993;0.01223;,
 -1.63645;2.83632;0.02542;,
 -1.63581;2.82802;-0.25869;,
 -1.36134;2.95036;-0.27641;,
 -1.67959;3.14003;-0.06856;,
 -1.68461;3.13085;-0.19335;,
 -1.57864;3.17371;-0.19224;,
 -1.57751;3.18948;-0.07776;;
 
 45;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 3;12,13,14;,
 3;13,15,14;,
 4;16,17,11,10;,
 4;18,19,7,6;,
 4;20,21,2,1;,
 4;22,23,24,25;,
 4;26,27,28,29;,
 3;30,31,32;,
 3;30,33,31;,
 4;27,26,34,35;,
 4;24,23,36,37;,
 4;38,39,40,41;,
 4;38,42,43,39;,
 3;21,44,45;,
 3;46,47,3;,
 4;48,49,50,51;,
 4;50,52,53,51;,
 4;52,54,55,53;,
 4;54,49,48,55;,
 4;51,46,45,48;,
 4;55,56,57,53;,
 3;57,43,47;,
 3;44,40,56;,
 3;43,57,39;,
 3;39,56,40;,
 3;39,57,56;,
 3;3,2,46;,
 3;2,45,46;,
 3;2,21,45;,
 3;46,57,47;,
 4;57,46,51,53;,
 3;44,56,45;,
 4;56,55,48,45;,
 4;49,58,59,50;,
 4;59,60,52,50;,
 4;60,61,54,52;,
 4;61,58,49,54;,
 4;59,62,63,60;,
 4;63,64,61,60;,
 4;64,65,58,61;,
 4;65,62,59,58;,
 4;65,64,63,62;;
 
 MeshMaterialList {
  1;
  45;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.250000;0.250000;0.250000;;
   TextureFilename {
    "model\\body.bmp";
   }
  }
 }
 MeshNormals {
  56;
  -0.053258;-0.321700;0.945343;,
  0.154549;-0.163660;0.974336;,
  0.036484;0.054275;0.997859;,
  -0.141823;-0.042037;0.988999;,
  -0.142614;-0.023319;0.989504;,
  0.041044;0.070712;0.996652;,
  0.062143;0.047612;0.996931;,
  -0.099396;-0.038463;0.994304;,
  0.079788;0.011332;0.996747;,
  0.221575;0.132078;0.966157;,
  0.222955;0.161731;0.961319;,
  0.213289;0.148354;0.965660;,
  0.389999;-0.067935;0.918306;,
  -0.034271;-0.061719;-0.997505;,
  -0.037724;-0.077573;-0.996273;,
  -0.021054;-0.106397;-0.994101;,
  0.095506;-0.291512;-0.951787;,
  0.519319;-0.094895;0.849295;,
  0.256731;-0.026703;0.966114;,
  -0.109784;-0.447300;0.887620;,
  -0.001470;-0.174668;0.984626;,
  -0.052348;0.268755;0.961785;,
  0.131188;-0.110540;0.985175;,
  -0.813765;-0.578869;0.051937;,
  -0.991124;-0.130160;0.027059;,
  0.000319;-0.195154;-0.980773;,
  -0.183463;0.131573;-0.974182;,
  -0.107499;-0.325923;-0.939265;,
  -0.107617;0.021050;-0.993969;,
  0.070759;-0.003587;0.997487;,
  -0.892687;-0.448274;0.046486;,
  -0.023347;-0.048539;-0.998548;,
  -0.989438;-0.142644;0.025775;,
  -0.113577;0.205622;-0.972019;,
  0.720606;0.689714;-0.070867;,
  -0.307486;-0.196357;-0.931073;,
  -0.289286;-0.203880;-0.935279;,
  -0.240639;-0.222024;-0.944880;,
  -0.000822;-0.136020;-0.990706;,
  0.199761;0.015973;-0.979715;,
  0.216995;0.055185;-0.974612;,
  0.242270;0.078914;-0.966994;,
  0.419157;-0.171167;-0.891633;,
  -0.173133;-0.481889;-0.858958;,
  0.963329;0.265645;-0.037803;,
  0.686725;0.724781;-0.055689;,
  -0.173560;-0.610002;-0.773159;,
  0.532795;-0.228793;-0.814729;,
  0.488855;-0.297845;-0.819945;,
  -0.059990;0.998186;0.005012;,
  -0.982449;0.186182;0.011421;,
  -0.808026;0.589116;0.006061;,
  0.408009;0.912021;-0.041800;,
  0.914862;0.401425;-0.043429;,
  -0.072058;0.296832;0.952207;,
  -0.408217;0.908848;-0.085758;;
  45;
  4;3,2,1,0;,
  4;3,4,5,2;,
  4;4,7,6,5;,
  3;7,8,6;,
  3;8,9,6;,
  4;9,10,5,6;,
  4;10,11,2,5;,
  4;11,12,1,2;,
  4;35,13,14,36;,
  4;14,15,37,36;,
  3;15,38,37;,
  3;15,39,38;,
  4;15,14,40,39;,
  4;14,13,41,40;,
  4;13,16,42,41;,
  4;13,35,43,16;,
  3;12,17,18;,
  3;20,19,0;,
  4;21,22,22,21;,
  4;23,23,24,24;,
  4;25,25,26,26;,
  4;44,44,45,45;,
  4;21,20,18,21;,
  4;26,28,27,26;,
  3;27,43,46;,
  3;47,42,48;,
  3;43,27,16;,
  3;16,48,42;,
  3;16,27,28;,
  3;0,1,20;,
  3;1,18,20;,
  3;1,12,18;,
  3;49,49,49;,
  4;50,50,24,24;,
  3;51,51,51;,
  4;52,45,45,52;,
  4;22,29,29,22;,
  4;30,30,23,23;,
  4;31,31,25,25;,
  4;53,53,44,44;,
  4;30,32,32,30;,
  4;33,33,31,31;,
  4;34,34,53,53;,
  4;54,54,29,29;,
  4;55,55,55,55;;
 }
 MeshTextureCoords {
  66;
  -0.568390;0.505990;
  -0.552470;0.499030;
  -0.560200;0.484270;
  -0.576310;0.492030;
  -0.567590;0.491710;
  -0.524140;0.555440;
  -0.510500;0.548680;
  -0.551670;0.484750;
  -0.534170;0.518050;
  -0.506290;0.570030;
  -0.489460;0.561480;
  -0.520520;0.511290;
  -0.518900;0.538220;
  -0.477140;0.567670;
  -0.502080;0.529680;
  -0.486060;0.524600;
  -0.473440;0.556400;
  -0.507490;0.506690;
  -0.497470;0.544080;
  -0.533830;0.476450;
  -0.534620;0.490730;
  -0.544250;0.476700;
  -0.558300;0.493830;
  -0.543600;0.486980;
  -0.501900;0.553080;
  -0.514850;0.557560;
  -0.506900;0.513380;
  -0.475760;0.562600;
  -0.491980;0.569840;
  -0.519860;0.517860;
  -0.524040;0.508930;
  -0.498500;0.545610;
  -0.540260;0.516170;
  -0.507420;0.502540;
  -0.493180;0.506500;
  -0.459140;0.556210;
  -0.524540;0.478570;
  -0.488180;0.546200;
  -0.525540;0.524110;
  -0.534910;0.510790;
  -0.516110;0.501660;
  -0.506480;0.515690;
  -0.540250;0.530950;
  -0.548170;0.516990;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;;
 }
}