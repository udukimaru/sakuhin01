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
 14;
 1.11519;-1.18924;0.26406;,
 0.55088;-0.19217;0.20276;,
 0.31724;-0.23298;0.31072;,
 0.87145;-1.20714;0.34584;,
 0.57242;-0.19755;-0.07243;,
 1.12761;-1.20777;0.02371;,
 0.89969;-1.20407;-0.10669;,
 0.29001;-0.25745;-0.22431;,
 0.66102;-1.18700;0.08133;,
 0.17933;-0.45701;0.01809;,
 -0.19260;0.13866;0.08166;,
 -0.17391;0.13938;-0.12352;,
 0.26835;0.07555;0.14293;,
 0.28524;0.06895;-0.07293;;
 
 16;
 4;0,1,2,3;,
 4;4,1,0,5;,
 4;4,5,6,7;,
 4;8,9,7,6;,
 4;3,2,9,8;,
 3;10,11,9;,
 3;9,11,7;,
 3;10,9,2;,
 4;11,10,12,13;,
 4;13,12,1,4;,
 3;13,4,7;,
 3;1,12,2;,
 3;2,12,10;,
 3;11,13,7;,
 3;8,6,3;,
 4;5,0,3,6;;
 
 MeshMaterialList {
  1;
  16;
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
    "model\\eye.bmp";
   }
  }
 }
 MeshNormals {
  24;
  0.195745;0.408321;0.891604;,
  0.336460;0.335731;-0.879818;,
  0.786078;0.617165;0.034489;,
  0.316284;0.366706;0.874923;,
  0.333614;0.234104;0.913180;,
  0.871943;0.488484;0.033152;,
  -0.385312;-0.835595;-0.391555;,
  0.464221;0.180461;-0.867141;,
  -0.701260;-0.514170;-0.493825;,
  -0.793480;-0.527780;0.303047;,
  -0.747586;-0.535939;-0.392280;,
  0.432441;0.901488;0.017711;,
  0.316372;0.796729;0.514909;,
  0.419333;0.290052;-0.860250;,
  -0.576832;-0.473389;-0.665709;,
  -0.239593;-0.939068;-0.246470;,
  -0.706034;-0.395643;0.587352;,
  -0.663750;-0.426011;0.614776;,
  0.143993;0.989578;-0.001195;,
  0.267064;0.408677;-0.872731;,
  -0.052637;0.470647;0.880750;,
  0.162523;0.417109;-0.894207;,
  -0.018199;-0.999754;0.012714;,
  0.044251;-0.998329;0.037156;;
  16;
  4;4,3,0,4;,
  4;2,2,5,5;,
  4;13,7,7,1;,
  4;6,8,14,15;,
  4;16,17,17,16;,
  3;9,10,8;,
  3;8,10,14;,
  3;9,17,17;,
  4;18,18,12,11;,
  4;11,12,2,2;,
  3;19,13,1;,
  3;3,12,0;,
  3;0,12,20;,
  3;21,19,1;,
  3;6,15,22;,
  4;23,23,22,15;;
 }
 MeshTextureCoords {
  14;
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
