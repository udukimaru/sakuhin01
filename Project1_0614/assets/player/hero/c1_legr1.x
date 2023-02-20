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
 37;
 1.37938;-2.43235;-1.75597;,
 1.39588;-1.69634;-1.75006;,
 1.44293;-1.64626;0.56149;,
 1.39962;-2.38906;0.58262;,
 -1.51685;-2.38906;0.58262;,
 -1.56017;-1.64626;0.56149;,
 -1.51311;-1.69634;-1.75006;,
 -1.49661;-2.43235;-1.75597;,
 -0.05862;-1.73498;-2.61276;,
 -0.05862;-2.44836;-2.61987;,
 -0.05862;-1.61642;1.56098;,
 -0.05862;-2.39055;1.54840;,
 -0.05862;-2.39055;1.54840;,
 -0.05862;-2.44836;-2.61987;,
 1.37938;-2.43235;-1.75597;,
 1.39962;-2.38906;0.58262;,
 -1.51685;-2.38906;0.58262;,
 -1.49661;-2.43235;-1.75597;,
 -0.05862;-1.61642;1.56098;,
 -0.05862;-1.73498;-2.61276;,
 -1.51311;-1.69634;-1.75006;,
 -1.56017;-1.64626;0.56149;,
 1.44293;-1.64626;0.56149;,
 1.39588;-1.69634;-1.75006;,
 0.67237;-0.03438;-0.57900;,
 0.69830;-0.10962;0.19196;,
 1.19739;-1.83697;0.41725;,
 1.16482;-1.90482;-1.24374;,
 -1.28205;-1.90482;-1.24374;,
 -1.31462;-1.83697;0.41725;,
 -0.80908;-0.01530;0.22551;,
 -0.78960;-0.03438;-0.57900;,
 -0.05862;0.09847;-0.96485;,
 -0.05862;-1.86888;-1.86028;,
 -0.07475;0.11068;0.65573;,
 -0.05862;-1.82499;1.32313;,
 -0.02839;0.53492;0.00745;;
 
 22;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;6,8,9,7;,
 4;0,9,8,1;,
 4;2,10,11,3;,
 4;4,11,10,5;,
 4;12,13,14,15;,
 4;16,17,13,12;,
 4;18,19,20,21;,
 4;22,23,19,18;,
 4;24,25,26,27;,
 4;28,29,30,31;,
 4;31,32,33,28;,
 4;27,33,32,24;,
 4;25,34,35,26;,
 4;29,35,34,30;,
 3;24,36,25;,
 3;30,36,31;,
 3;24,32,36;,
 3;36,32,31;,
 3;36,34,25;,
 3;30,34,36;;
 
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
  30;
  0.883945;-0.029404;0.466666;,
  0.865930;-0.022079;-0.499677;,
  -0.883945;-0.029404;0.466666;,
  -0.865930;-0.022080;-0.499677;,
  -0.512571;0.002004;-0.858643;,
  0.553052;-0.011082;0.833073;,
  0.803438;0.369841;-0.466588;,
  0.851013;0.302917;0.428974;,
  0.745053;0.557286;0.366509;,
  0.692387;0.641172;-0.330906;,
  -0.802188;0.365325;-0.472263;,
  -0.851685;0.294611;0.433402;,
  -0.717156;0.604247;0.347236;,
  -0.667099;0.656496;-0.352124;,
  0.002099;0.720341;-0.693617;,
  -0.000001;0.428111;-0.903726;,
  0.548846;0.506826;0.664752;,
  0.558406;0.270701;0.784158;,
  0.186652;0.980248;0.065380;,
  0.512571;0.002004;-0.858642;,
  -0.553052;-0.011082;0.833073;,
  0.000000;-0.999869;0.016187;,
  0.005109;-0.999856;0.016187;,
  -0.005109;-0.999856;0.016187;,
  -0.000000;0.999690;-0.024887;,
  0.006456;0.999669;-0.024886;,
  -0.006456;0.999669;-0.024886;,
  -0.545267;0.257692;0.797671;,
  -0.504177;0.543524;0.671109;,
  -0.581971;0.812525;-0.033364;;
  22;
  4;1,1,0,0;,
  4;2,2,3,3;,
  4;3,4,4,3;,
  4;1,19,19,1;,
  4;0,5,5,0;,
  4;2,20,20,2;,
  4;21,21,22,22;,
  4;23,23,21,21;,
  4;24,24,25,25;,
  4;26,26,24,24;,
  4;9,8,7,6;,
  4;10,11,12,13;,
  4;13,14,15,10;,
  4;6,15,14,9;,
  4;8,16,17,7;,
  4;11,27,28,12;,
  3;9,18,8;,
  3;12,29,13;,
  3;9,14,18;,
  3;18,14,13;,
  3;18,16,8;,
  3;12,28,18;;
 }
 MeshTextureCoords {
  37;
  -0.158630;0.309310;
  -0.157980;0.275760;
  -0.156160;0.273480;
  -0.157840;0.307330;
  -0.271150;0.307330;
  -0.272830;0.273480;
  -0.271000;0.275760;
  -0.270360;0.309310;
  -0.214490;0.277520;
  -0.214490;0.310040;
  -0.214490;0.272120;
  -0.214490;0.307400;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  -0.170790;0.561290;
  -0.156230;0.654590;
  -0.231920;0.637430;
  -0.242300;0.585770;
  -0.092300;0.581490;
  -0.086620;0.633270;
  -0.109330;0.596610;
  -0.108640;0.599400;
  -0.067500;0.689670;
  -0.070090;0.693180;
  -0.265050;0.693180;
  -0.267640;0.689670;
  -0.226500;0.599400;
  -0.225810;0.596610;
  -0.167570;0.589750;
  -0.167570;0.691320;
  -0.167570;0.591180;
  -0.167570;0.689060;
  -0.167570;0.566820;;
 }
}