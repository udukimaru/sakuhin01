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
 22;
 0.70824;-1.42379;-0.49259;,
 0.70824;-0.98008;-0.50811;,
 1.21124;-0.97736;-0.24228;,
 1.21147;-1.42733;-0.24537;,
 0.20500;-1.42733;-0.24537;,
 0.20524;-0.97736;-0.24228;,
 0.70824;-0.98768;0.66025;,
 0.70824;-1.42620;0.65867;,
 1.21342;-1.42221;0.38506;,
 1.20969;-0.98615;0.38229;,
 0.20679;-0.98615;0.38229;,
 0.20306;-1.42221;0.38506;,
 0.70824;-0.66103;0.08777;,
 0.70824;-1.76764;0.06865;,
 -0.34260;0.10125;-0.20921;,
 0.12339;0.30812;-0.29655;,
 0.84299;-1.02093;-0.13983;,
 0.43655;-1.25146;-0.02994;,
 0.15086;0.41515;0.18627;,
 0.90028;-0.93996;0.32776;,
 -0.31423;0.19346;0.28262;,
 0.51451;-1.15134;0.42674;;
 
 22;
 4;0,1,2,3;,
 4;1,0,4,5;,
 4;6,7,8,9;,
 4;7,6,10,11;,
 4;3,2,9,8;,
 4;5,4,11,10;,
 3;9,2,12;,
 3;5,10,12;,
 3;12,2,1;,
 3;5,12,1;,
 3;9,12,6;,
 3;12,10,6;,
 3;11,4,13;,
 3;3,8,13;,
 3;11,13,7;,
 3;13,8,7;,
 3;13,4,0;,
 3;3,13,0;,
 4;14,15,16,17;,
 4;16,15,18,19;,
 4;19,18,20,21;,
 4;14,17,21,20;;
 
 MeshMaterialList {
  1;
  22;
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
    "model\\taroimo.bmp";
   }
  }
 }
 MeshNormals {
  28;
  -0.000000;-0.013769;-0.999905;,
  -0.000000;-0.514876;-0.857264;,
  -0.000000;0.003723;0.999993;,
  0.454190;-0.012267;-0.890820;,
  0.393270;-0.473389;-0.788189;,
  -0.454191;-0.012267;-0.890820;,
  -0.393270;-0.473389;-0.788189;,
  0.422257;0.478132;0.770123;,
  0.425205;-0.471875;0.772357;,
  -0.422258;0.478132;0.770122;,
  -0.425205;-0.471875;0.772356;,
  0.126235;0.991924;0.012332;,
  -0.134296;-0.990887;-0.010359;,
  -0.125507;-0.191605;-0.973414;,
  0.872456;0.458542;-0.168997;,
  0.133288;0.180540;0.974495;,
  0.884882;-0.465807;0.002633;,
  0.710192;0.681085;-0.178186;,
  0.875982;0.482287;0.007320;,
  -0.710192;0.681085;-0.178186;,
  -0.884882;-0.465807;0.002633;,
  -0.875983;0.482287;0.007320;,
  -0.538500;0.842522;0.013188;,
  -0.000000;0.881589;-0.472018;,
  -0.000000;0.868560;0.495583;,
  0.562300;-0.826918;0.004979;,
  -0.000000;-0.865522;0.500870;,
  -0.852794;-0.484236;0.195596;;
  22;
  4;1,0,3,4;,
  4;0,1,6,5;,
  4;2,2,8,7;,
  4;2,2,9,10;,
  4;16,17,18,16;,
  4;19,20,20,21;,
  3;18,17,11;,
  3;19,21,22;,
  3;11,17,23;,
  3;19,11,23;,
  3;7,11,24;,
  3;11,9,24;,
  3;20,20,12;,
  3;16,16,25;,
  3;10,12,26;,
  3;12,8,26;,
  3;12,6,1;,
  3;4,12,1;,
  4;13,13,13,13;,
  4;14,14,14,14;,
  4;15,15,15,15;,
  4;27,27,27,27;;
 }
 MeshTextureCoords {
  22;
  -0.579840;0.509840;
  -0.579840;0.457150;
  -0.643250;0.456830;
  -0.643280;0.510260;
  -0.516400;0.510260;
  -0.516430;0.456830;
  -0.579840;0.458050;
  -0.579840;0.510120;
  -0.643530;0.509650;
  -0.643060;0.457870;
  -0.516630;0.457870;
  -0.516160;0.509650;
  -0.579840;0.419270;
  -0.579840;0.550670;
  -0.248180;0.413770;
  -0.272510;0.397190;
  -0.310790;0.501110;
  -0.289600;0.519510;
  -0.273900;0.388980;
  -0.313760;0.494920;
  -0.249620;0.406730;
  -0.293640;0.511800;;
 }
}
