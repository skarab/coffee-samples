/header q   CLZ �   �1.0    O   resource::Chunk A?   - �LODArray" �LOD  "  ;S  % 
 ES �Parameters"  �     ����/lod0 !  CLZ �'  �1.0    P   meta::ObjectPointer A<   5  	$   S    �5  graphics::Shader �$  resourceK �]      S 6  �   �  Properties
 &y Q  1Bas1 (@ 1 Z B �    TexturZ / X 
p    Ren� 8tat�  �   '  VertexBuff `uint32  O   ;�� FilePath storag�   @   	ZKtampL �# 	 ?  |t�    � �pbasic:: H ��  Geometry"  Q�Fragment" &OD XInput� �HADER_SOURCE_INPUT� 3 ?Out4 	?OUT5  2Max8 � ' � � #�/�LineArray `String S�  ��   #version 130 x ��%   uniform mat4 world_to_camera_matrix; 
6 �      varying vec2 uv;     �3 view_vector; D 1  / �void main() I{� �       uv = gl_MultiTexCoord0.xy;� H' g � = (vec4(gl_Color.xyz, 0.0)*� )" t;    P �ec4 pos = ftrans!�();    % �pos.z = 0.9 s;     �gl_Positw=, 3; � 4} 
�/8 �"  < /K< �  U    �- Qexten �GL_ARB_tj�_rectangle : enable ;5 �EXT_gpu_sf4/ 1  E�// Default helpers 1  ( [�PackDepth(float d 5) / �3uareturn� / 2or(/ �/256.0, fract E); !�"| #� m 5Unp � ~ $~  A$~ ` 1.x*u + Uy); &o 'o (u- � qNormal( n 5) )n *an % u+1.0; +a ,a -Ma � c .c /c -c 0c 1c  �M��ComputeParallax(,3eye�", bdheight `strengb3� 4�N ��� Fize(_ )#S5   .; o # =s *l % -w  /2� 6�9uv+v S*h; 7�d}    8T9   pARGBE�U v) :� Y;   !� �exp = v.w*255.0-128� <�	� ��*exp2(exp); =�>� ?�o#ifdef� ;[� AAppl.2owsc5�, sampler2DRect s" �lI�_softness,5) A� B��  / " = (B �>0.01); C��� p*((1.0-/  )+ *� � (� �uv).x); D'E�#endif F6WG   &
� bX ;� $. Fbase, I�, hmateri\ J0 � ambient�lod0; K0 O1; L0 O2; M0 D3; NSOS_!2;. ,Qky_inXTty; Q\ R�S�TD U� V�VW   7v�3 albedo = s�q MXn
��A E 3; Y�� �* =�
O 
�� �); Z   >O J +	 %	
2�  96F Frefl}  �s$),f3; \4 > <$ � �S^   :  �.x = 1.0+atang S.x, -  z)��/3.14159; _�B �y = acos> &y)/ `� awrrgbe0 =�n(�,n `)); //P( b�
O 1O 1O O33 cP 2P 2P O66 d� 3P 3P  �eKf�	
�� = clamp�a.y*1.2|,B �); g   =� s0Amix(�,C@, s/")*@tep( 0, s�	h'E 2E 1E a2, (s-F L  !66L *[ 7; iIZ 3Z 2Z 3Z $66Z 	U y; j   Caa �ps1+s2+s5 *4"x*� *4'ktl�0gl_�! =��lmnF o p�?q  ��\Flags,H  �@s   `upP $wP  ��x   y   z�1  |� �  ~     �##|�FaceCullingMod!EN��TATE_FACE_CULLING� �FrontPolygon< 	�POLYGON_MODE< OBack; $�QTestEGsd bool � @FuncqZ �TEST_FUNCTION[ Writing^ ) � lW �� L� la	Q  � Fa%[ �BLENDING�<TOR_ pDestina� H "_AlphaW W"> �Threshold real �v��   ������� �"�6�. �4� � � �" �G�8 ?� �� �?�  D #� �NType��PROPERTY_TYP�TValue�
��jEvalua�Q gEVALUA��S�   ��t� ��� S�   �� u� ����9 ��� ��vS�   ��y� ��� S�   �tz� ��� S�   ��{� ��� S�   �|� ��� S�   � }� ��� S�   ��~� ��� S�   �� �<c  %& 3 M ! �\ =�?   ��� � 2� �� 4���  w 	�b
��D����S/-H  
�) g?  � /� ��� �XmeterD�TEXTURE_PARAMETER���-��}� /coffee/import/� ts/null.� �g �� �35 i�;�;��;�g �;�;1;�;��;�g �;�;2;�;��;�g �;�;3;�;��;�g �; i/; BD#�7��7�g �7 �+7 ]�3�3��3�g ��           