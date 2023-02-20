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
 -0.57430;2.79103;-1.05371;,
 -0.70919;-0.44994;-1.24403;,
 -1.09083;-0.27425;-0.18976;,
 -0.97773;2.89681;-0.11883;,
 0.97773;2.89681;-0.11883;,
 1.09083;-0.27425;-0.18976;,
 0.70919;-0.44994;-1.24403;,
 0.57430;2.79103;-1.05371;,
 0.97773;2.89681;-0.11883;,
 0.60215;2.69504;0.81855;,
 0.71264;-0.45187;0.86552;,
 1.09083;-0.27425;-0.18976;,
 -1.09083;-0.27425;-0.18976;,
 -0.71264;-0.45187;0.86552;,
 -0.60215;2.69504;0.81855;,
 -0.97773;2.89681;-0.11883;,
 1.09083;-0.27425;-0.18976;,
 0.33322;-1.51303;-0.24510;,
 0.70919;-0.44994;-1.24403;,
 -0.70919;-0.44994;-1.24403;,
 -0.33322;-1.51303;-0.24510;,
 -1.09083;-0.27425;-0.18976;,
 0.71264;-0.45187;0.86552;,
 -0.71264;-0.45187;0.86552;;
 
 12;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;13,10,9,14;,
 4;6,1,0,7;,
 3;16,17,18;,
 3;19,20,21;,
 3;16,22,17;,
 3;20,23,21;,
 4;17,20,19,18;,
 4;22,23,20,17;;
 
 MeshMaterialList {
  1;
  12;
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
  20;
  -0.999000;0.044006;-0.007892;,
  -0.966425;-0.256870;-0.006452;,
  -0.920971;-0.235848;-0.310143;,
  -0.925918;0.050519;-0.374332;,
  0.999000;0.044006;-0.007892;,
  0.966425;-0.256870;-0.006452;,
  0.920971;-0.235848;-0.310143;,
  0.925918;0.050519;-0.374332;,
  0.932561;0.031347;0.359650;,
  0.920372;-0.253564;0.297692;,
  -0.932561;0.031347;0.359650;,
  -0.920372;-0.253564;0.297692;,
  0.853188;-0.521583;-0.004532;,
  -0.853188;-0.521583;-0.004532;,
  0.000000;-0.386304;0.922371;,
  0.000000;0.014923;0.999889;,
  0.000000;-0.340848;-0.940118;,
  0.000000;0.058622;-0.998280;,
  0.000000;-0.684774;-0.728756;,
  0.000000;-0.723022;0.690825;;
  12;
  4;3,2,1,0;,
  4;4,5,6,7;,
  4;4,8,9,5;,
  4;1,11,10,0;,
  4;14,14,15,15;,
  4;16,16,17,17;,
  3;5,12,6;,
  3;2,13,1;,
  3;5,9,12;,
  3;13,11,1;,
  4;18,18,16,16;,
  4;14,14,19,19;;
 }
 MeshTextureCoords {
  24;
  -0.226490;0.654680;
  -0.259820;0.964710;
  -0.306620;0.955770;
  -0.293930;0.651910;
  -0.037310;0.651910;
  -0.024620;0.955770;
  -0.071410;0.964710;
  -0.104750;0.654680;
  -0.089120;0.366050;
  -0.130640;0.370680;
  -0.114960;0.486410;
  -0.080250;0.482680;
  -0.277170;0.482680;
  -0.242470;0.486410;
  -0.226780;0.370680;
  -0.268310;0.366050;
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
