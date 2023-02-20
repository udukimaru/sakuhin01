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
 24;
 -0.00000;-0.50184;0.74508;,
 -0.00000;-0.75000;0.65121;,
 0.56700;-0.75000;0.50093;,
 0.45138;-0.12424;0.86323;,
 0.65121;-0.50184;0.43293;,
 0.63362;-0.75000;-0.00000;,
 0.97787;-0.12424;-0.00000;,
 -0.97786;-0.12424;0.00000;,
 -0.63362;-0.75000;0.00000;,
 -0.56700;-0.75000;0.50093;,
 -0.65120;-0.50184;0.43293;,
 -0.45138;-0.12424;0.86323;,
 -0.00000;-0.75000;0.00000;,
 -0.00000;-0.50184;-0.74508;,
 0.45138;-0.12424;-0.86323;,
 0.56700;-0.75000;-0.50093;,
 -0.00000;-0.75000;-0.65121;,
 0.65121;-0.50184;-0.43293;,
 0.56700;-0.75000;-0.50093;,
 -0.65120;-0.50184;-0.43293;,
 -0.56700;-0.75000;-0.50093;,
 -0.45138;-0.12424;-0.86323;,
 0.65121;-0.50184;-0.43293;,
 0.45138;-0.12424;-0.86323;;
 
 28;
 4;0,1,2,3;,
 4;4,2,5,6;,
 4;7,8,9,10;,
 4;11,9,1,0;,
 3;12,0,3;,
 3;12,3,4;,
 3;12,4,6;,
 3;12,7,10;,
 3;12,10,11;,
 3;12,11,0;,
 3;9,11,10;,
 3;2,4,3;,
 4;12,2,1,9;,
 4;13,14,15,16;,
 4;17,6,5,18;,
 4;7,19,20,8;,
 4;21,13,16,20;,
 3;12,14,13;,
 3;12,22,14;,
 3;12,6,22;,
 3;12,19,7;,
 3;12,21,19;,
 3;12,13,21;,
 3;20,19,21;,
 3;18,23,17;,
 4;12,20,16,15;,
 4;12,9,8,20;,
 4;12,15,5,2;;
 
 MeshMaterialList {
  1;
  28;
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
   1.000000;0.980392;0.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.500000;0.490196;0.000000;;
  }
 }
 MeshNormals {
  36;
  -0.059504;0.997571;-0.036205;,
  0.922051;-0.387069;-0.000000;,
  -0.922050;-0.387070;0.000000;,
  -0.000000;-0.417066;0.908876;,
  0.569439;-0.300276;0.765227;,
  0.894542;-0.268266;0.357530;,
  -0.894541;-0.268269;0.357530;,
  -0.569439;-0.300279;0.765226;,
  -0.000000;-0.417066;-0.908876;,
  0.569439;-0.300276;-0.765227;,
  0.894542;-0.268266;-0.357530;,
  -0.894541;-0.268269;-0.357530;,
  -0.569439;-0.300279;-0.765226;,
  0.906759;-0.380650;0.181367;,
  -0.204409;-0.408260;0.889686;,
  -0.579455;0.773243;-0.257539;,
  -0.250249;0.841357;-0.479055;,
  0.119520;0.773099;-0.622923;,
  -0.512171;0.800356;0.311628;,
  -0.539011;0.842299;0.000000;,
  0.512171;0.800356;0.311627;,
  0.539011;0.842299;0.000000;,
  -0.119520;0.773099;-0.622923;,
  0.250248;0.841357;-0.479055;,
  0.579454;0.773244;-0.257539;,
  0.000000;-1.000000;-0.000000;,
  0.906759;-0.380650;-0.181367;,
  -0.204409;-0.408260;-0.889686;,
  -0.250249;0.841357;0.479055;,
  -0.579455;0.773243;0.257539;,
  0.119520;0.773099;0.622923;,
  -0.512171;0.800356;-0.311628;,
  0.512171;0.800356;-0.311627;,
  0.250248;0.841357;0.479055;,
  -0.119520;0.773099;0.622923;,
  0.579454;0.773244;0.257539;;
  28;
  4;3,3,4,4;,
  4;5,13,1,1;,
  4;2,2,6,6;,
  4;7,14,3,3;,
  3;0,15,16;,
  3;0,16,17;,
  3;0,18,19;,
  3;20,21,20;,
  3;0,22,23;,
  3;0,23,24;,
  3;6,7,6;,
  3;4,5,4;,
  4;25,25,25,25;,
  4;8,9,9,8;,
  4;10,1,1,26;,
  4;2,11,11,2;,
  4;12,8,8,27;,
  3;0,28,29;,
  3;0,30,28;,
  3;0,19,31;,
  3;0,32,21;,
  3;0,33,34;,
  3;0,35,33;,
  3;11,11,12;,
  3;9,9,10;,
  4;25,25,25,25;,
  4;25,25,25,25;,
  4;25,25,25,25;;
 }
 MeshTextureCoords {
  24;
  0.496312;-0.174910;
  0.495265;-0.257390;
  0.629960;-0.259035;
  0.572933;-0.050715;
  0.652662;-0.176799;
  0.750000;-0.259228;
  0.750000;-0.052242;
  0.250000;-0.046570;
  0.250000;-0.255552;
  0.364483;-0.255745;
  0.343304;-0.173021;
  0.422951;-0.048097;
  0.250000;-0.257390;
  0.003688;-0.174910;
  -0.072933;-0.050715;
  -0.129960;-0.259035;
  0.004735;-0.257390;
  0.847338;-0.176799;
  0.870040;-0.259035;
  0.156696;-0.173021;
  0.135517;-0.255745;
  0.077049;-0.048097;
  -0.152662;-0.176799;
  0.927067;-0.050715;;
 }
}
