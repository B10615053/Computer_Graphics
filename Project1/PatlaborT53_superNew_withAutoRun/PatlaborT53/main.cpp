#include "main.h"
#include "CubemapShader.h"

int main(int argc, char** argv)
{
	winWidth = 800;
	winHeight = 600;

	// Initial GLUT and create window
	glutInit(&argc, argv);
	glutInitContextVersion(4, 3);// Base on OpenGL version 4.3
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);// Check downward compatibility GLUT_FORWARD_COMPATIBLE
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);// Multisample for polygons smooth
	//glAlphaFunc
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Patlabor_T53");

	// Call custom initialize function
	glewExperimental = GL_TRUE;// Position before glewInit()
	if (glewInit())
	{
		// C error catch
		cerr << "Unable to initialize GLEW ... exiting" << endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		// Print debug information
		dumpInformation();
	}
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	init();

	// Register callbacks & render function
	glutDisplayFunc(display);
	glutReshapeFunc(ChangeSize);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutPassiveMotionFunc(motion);

	// Initial right botton menu

	// Add mode right botton object
	int	modeMenu = glutCreateMenu(ModeMenuEvents);
	glutAddMenuEntry("Line", 0);
	glutAddMenuEntry("Fill", 1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// Add scene right botton object
	int	sceneMenu = glutCreateMenu(SceneMenuEvents);
	glutAddMenuEntry("Hangar", 0);
	glutAddMenuEntry("Sea", 1);
	glutAddMenuEntry("Daze", 2);
	glutAddMenuEntry("XY coordinate", 3);
	glutAddMenuEntry("Dark clouds", 4);
	glutAddMenuEntry("Spinning", 5);
	glutAddMenuEntry("Sun", 6);
	glutAddMenuEntry("Sine waves", 7);
	glutAddMenuEntry("Black hole", 8);
	glutAddMenuEntry("Shining star", 9);
	glutAddMenuEntry("Distorted", 10);
	glutAddMenuEntry("Noise", 11);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// Add action to  right botton object
	int actionMenu = glutCreateMenu(ActionMenuEvents);
	glutAddMenuEntry("Attention", 0); // Attention
	glutAddMenuEntry("At Ease", 1);// At Ease
	glutAddMenuEntry("Salute", 2); // Salute
	glutAddMenuEntry("Walk", 3); // Walking
	glutAddMenuEntry("Run", 4); // Walking
	glutAddMenuEntry("Squats", 5); // Squats
	glutAddMenuEntry("Jump", 6); // Jump
	glutAddMenuEntry("Petanque", 7); // Petanque
	glutAddMenuEntry("Lose", 8); // Lose
	glutAddMenuEntry("Breaking-Kick&Step", 9); // Breaking-Kick&Step
	glutAddMenuEntry("Breaking-ICE", 10); // ICE
	glutAddMenuEntry("Locking-Wrist Twirl", 11); //Locking-Wrist Twirl
	glutAddMenuEntry("Locking-Scooba Hop", 12); //Locking-Scooba Hop
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	int shaderMenu = glutCreateMenu(ShaderMenuEvents);
	glutAddMenuEntry("Normal", 0);
	glutAddMenuEntry("Purple", 1);
	glutAddMenuEntry("Transparent", 2);
	glutAddMenuEntry("Gray scale", 3);
	//glutAddMenuEntry("Colorful", 4);
	glutAddMenuEntry("Complement", 4);
	glutAddMenuEntry("Black and white", 5);
	//glutAddMenuEntry("Ghost", 7);
	//glutAddMenuEntry("Black dots", 8);
	//glutAddMenuEntry("Water flow", 9);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// Build right botton menu
	glutCreateMenu(menuEvents);

	// Add main object to right botton
	glutAddSubMenu("Mode", modeMenu);
	glutAddSubMenu("Scene", sceneMenu);
	glutAddSubMenu("Action", actionMenu);
	glutAddSubMenu("Shader", shaderMenu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// Timer
	glutTimerFunc(interval, idle, 0);
	//glutTimerFunc(autoRunInterval, autoRun, 0);

	// Special Key
	glutSpecialFunc(Special);

	// Enter GLUT event procession cycle
	glutMainLoop();
	return 0;
}

// Information
void dumpInformation()
{
	std::cout << "Vender: " << glGetString(GL_VENDOR) << std::endl
		<< "Renderer: " << glGetString(GL_RENDERER) << std::endl
		<< "Version: " << glGetString(GL_VERSION) << std::endl
		<< "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}


// Initial Parts
// Initial function
void init()
{
	ShaderInfo pointSpiteShader[] = {
		{ GL_VERTEX_SHADER, "Point_Sprite.vs.glsl" }, // vertex shader
	{ GL_FRAGMENT_SHADER, "Point_Sprite.fs.glsl" }, // fragment shader
	{ GL_NONE, NULL } };
	pointSpriteProgID = LoadShaders(pointSpiteShader);
	glUseProgram(pointSpriteProgID);

	cubemapShader.genPointSprite(pointSpriteProgID);


	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glDepthFunc(GL_LEQUAL);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	isFrame = false;
	frameCounter = 0;
	shaderNo = 0;
	sceneNo = 0;
	/*
	for (int i = 0; i < PARTSNUM; i++)
		angle[i] = 0;
		*/
	// Initial
	for (int i = 0; i < PARTSNUM; i++)
	{
		modelAngle[i].X = 0;
		modelAngle[i].Y = 0;
		modelAngle[i].Z = 0;
	}

	//VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, "DSPhong_Material.vp" },//vertex shader
	{ GL_FRAGMENT_SHADER, "DSPhong_Material0.fp" },//fragment shader
	{ GL_NONE, NULL } };
	program = LoadShaders(shaders);

	glUseProgram(program);

	MatricesIdx = glGetUniformBlockIndex(program, "MatVP");
	ModelID = glGetUniformLocation(program, "Model");
	M_KaID = glGetUniformLocation(program, "Material.Ka");
	M_KdID = glGetUniformLocation(program, "Material.Kd");
	M_KsID = glGetUniformLocation(program, "Material.Ks");
	//or
	/*M_KdID = M_KaID+1;
	M_KsID = M_KaID+2;*/

	Projection = glm::perspective(80.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	//glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

	// Camera matrix
	lookDistance = 0;
	View = glm::lookAt(
		glm::vec3(0, 10, 25), // Camera is at (0,10,25), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,1,0 to look upside-down)
	);

	Obj2Buffer();

	//UBO
	glGenBuffers(1, &UBO);
	glBindBuffer(GL_UNIFORM_BUFFER, UBO);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(mat4) * 2, NULL, GL_DYNAMIC_DRAW);
	//get uniform struct size
	int UBOsize = 0;
	glGetActiveUniformBlockiv(program, MatricesIdx, GL_UNIFORM_BLOCK_DATA_SIZE, &UBOsize);
	//bind UBO to its idx
	glBindBufferRange(GL_UNIFORM_BUFFER, 0, UBO, 0, UBOsize);
	glUniformBlockBinding(program, MatricesIdx, 0);


	glClearColor(1.0, 0.0, 0.0, 1);

	std::vector<CubemapTexture> textures(6);

	// set texture data
	textures[0].type = GL_TEXTURE_CUBE_MAP_POSITIVE_X;
	textures[0].fileName = cubeFilesName[sceneNo]->right;

	textures[1].type = GL_TEXTURE_CUBE_MAP_NEGATIVE_X;
	textures[1].fileName = cubeFilesName[sceneNo]->left;

	textures[2].type = GL_TEXTURE_CUBE_MAP_POSITIVE_Y;
	textures[2].fileName = cubeFilesName[sceneNo]->down;

	textures[3].type = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y;
	textures[3].fileName = cubeFilesName[sceneNo]->top;

	textures[4].type = GL_TEXTURE_CUBE_MAP_POSITIVE_Z;
	textures[4].fileName = cubeFilesName[sceneNo]->front;

	textures[5].type = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z;
	textures[5].fileName = cubeFilesName[0]->back;

	// initialize cubemap shader
	cubemapShader.Init(textures, 0);
}

// Load model data to Buffer
void Obj2Buffer()
{
	std::vector<vec3> Kds;
	std::vector<vec3> Kas;
	std::vector<vec3> Kss;
	std::vector<std::string> Materials;//mtl-name
	std::string texture;
	loadMTL("Patlabor_T53/Patlabor_T53.mtl", Kds, Kas, Kss, Materials, texture);
	for (int i = 0; i < Materials.size(); i++)
	{
		string mtlname = Materials[i];
		// name        vec3
		KDs[mtlname] = Kds[i];
	}
	// Body
	load2Buffer("Patlabor_T53/body.obj", BODY);
	// Head
	load2Buffer("Patlabor_T53/head.obj", HEAD);
	// Left arm
	load2Buffer("Patlabor_T53/leftUpperArm.obj", LEFTUPPERARM);
	load2Buffer("Patlabor_T53/leftLowerArm.obj", LEFTLOWERARM);
	load2Buffer("Patlabor_T53/leftHand.obj", LEFTHAND);
	// Right arm
	load2Buffer("Patlabor_T53/rightUpperArm.obj", RIGHTUPPERARM);
	load2Buffer("Patlabor_T53/rightLowerArm.obj", RIGHTLOWERARM);
	load2Buffer("Patlabor_T53/rightHand.obj", RIGHTHAND);
	// Left leg
	load2Buffer("Patlabor_T53/leftThigh.obj", LEFTTHIGH);
	load2Buffer("Patlabor_T53/leftShank.obj", LEFTSHANK);
	load2Buffer("Patlabor_T53/leftFoot.obj", LEFTFOOT);
	// Right leg
	load2Buffer("Patlabor_T53/rightThigh.obj", RIGHTTHIGH);
	load2Buffer("Patlabor_T53/rightShank.obj", RIGHTSHANK);
	load2Buffer("Patlabor_T53/rightFoot.obj", RIGHTFOOT);

	GLuint totalSize[3] = { 0,0,0 };
	GLuint offset[3] = { 0,0,0 };
	for (int i = 0; i < PARTSNUM; i++)
	{
		totalSize[0] += vertices_size[i] * sizeof(vec3);
		totalSize[1] += uvs_size[i] * sizeof(vec2);
		totalSize[2] += normals_size[i] * sizeof(vec3);
	}
	//generate vbo
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &uVBO);
	glGenBuffers(1, &nVBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, totalSize[0], NULL, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, uVBO);
	glBufferData(GL_ARRAY_BUFFER, totalSize[1], NULL, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, nVBO);
	glBufferData(GL_ARRAY_BUFFER, totalSize[2], NULL, GL_STATIC_DRAW);

	for (int i = 0; i < PARTSNUM; i++)
	{
		glBindBuffer(GL_COPY_WRITE_BUFFER, VBO);
		glBindBuffer(GL_COPY_READ_BUFFER, VBOs[i]);
		glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, offset[0], vertices_size[i] * sizeof(vec3));
		offset[0] += vertices_size[i] * sizeof(vec3);
		glInvalidateBufferData(VBOs[i]);//free vbo
		glBindBuffer(GL_COPY_WRITE_BUFFER, 0);

		glBindBuffer(GL_COPY_WRITE_BUFFER, uVBO);
		glBindBuffer(GL_COPY_READ_BUFFER, uVBOs[i]);
		glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, offset[1], uvs_size[i] * sizeof(vec2));
		offset[1] += uvs_size[i] * sizeof(vec2);
		glInvalidateBufferData(uVBOs[i]);//free vbo
		glBindBuffer(GL_COPY_WRITE_BUFFER, 0);

		glBindBuffer(GL_COPY_WRITE_BUFFER, nVBO);
		glBindBuffer(GL_COPY_READ_BUFFER, nVBOs[i]);
		glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, offset[2], normals_size[i] * sizeof(vec3));
		offset[2] += normals_size[i] * sizeof(vec3);
		glInvalidateBufferData(nVBOs[i]);//free vbo
		glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
	}
	glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
}

// Load Obj to buffer
void load2Buffer(const char* obj, int i)
{
	std::vector<vec3> vertices;
	std::vector<vec2> uvs;
	std::vector<vec3> normals; // Won't be used at the moment.
	std::vector<unsigned int> materialIndices;

	bool res = loadOBJ(obj, vertices, uvs, normals, triangleFaces[i], mtls[i]);
	if (!res) printf("load failed\n");

	//glUseProgram(program);

	glGenBuffers(1, &VBOs[i]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[i]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), &vertices[0], GL_STATIC_DRAW);
	vertices_size[i] = vertices.size();

	//vertices_size[i] = glm_model->numtriangles;

	//printf("vertices:%d\n",vertices_size[);

	glGenBuffers(1, &uVBOs[i]);
	glBindBuffer(GL_ARRAY_BUFFER, uVBOs[i]);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(vec2), &uvs[0], GL_STATIC_DRAW);
	uvs_size[i] = uvs.size();

	glGenBuffers(1, &nVBOs[i]);
	glBindBuffer(GL_ARRAY_BUFFER, nVBOs[i]);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(vec3), &normals[0], GL_STATIC_DRAW);
	normals_size[i] = normals.size();
}

// Display Part
// Display function
void display()
{
	prepared4AutoRun = true;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (sceneNo == 5)
		cubemapShader.drawPointSprite(pointSpriteProgID, Projection, mouseX, mouseY, winWidth, winHeight, 1);
	if (sceneNo == 8)
		cubemapShader.drawPointSprite(pointSpriteProgID, Projection, mouseX, mouseY, winWidth, winHeight, 0);

	// use program
	cubemapShader.Enable();
	// set uniform variables
	cubemapShader.SetMVMat(glm::mat4(glm::mat3(View)));
	cubemapShader.SetPMat(Projection);
	cubemapShader.SetTime(frameCounter++);
	cubemapShader.SetMouse(mouseX, mouseY, winWidth, winHeight);
	cubemapShader.setResolution(winWidth, winHeight);
	// draw elements
	cubemapShader.Render();
	// stop using program
	cubemapShader.Disable();

	glBindVertexArray(VAO);
	glUseProgram(program);
	float eyey = DOR(eyeAngley);
	View = lookAt(
		vec3(eyedistance * sin(eyey), 2, eyedistance * cos(eyey)), // Camera is at (0,0,20), in World Space
		vec3(0, lookDistance, 0), // and looks at the origin
		vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);
	updateModels();
	//update data to UBO for MVP
	glBindBuffer(GL_UNIFORM_BUFFER, UBO);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(mat4), &View);
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(mat4), sizeof(mat4), &Projection);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	GLuint offset[3] = { 0,0,0 };//offset for vertices , uvs , normals
	for (int i = 0; i < PARTSNUM; i++) {
		glUniformMatrix4fv(ModelID, 1, GL_FALSE, &models[i][0][0]);

		glUniform1i(partLocation, i);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0,				//location
			3,				//vec3
			GL_FLOAT,			//type
			GL_FALSE,			//not normalized
			0,				//strip
			(void*)offset[0]);//buffer offset
		offset[0] += vertices_size[i] * sizeof(vec3);

		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(1);//location 1 :vec2 UV
		glBindBuffer(GL_ARRAY_BUFFER, uVBO);
		glVertexAttribPointer(1,
			2,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)offset[1]);
		offset[1] += uvs_size[i] * sizeof(vec2);

		// 3rd attribute buffer : normals
		glEnableVertexAttribArray(2);//location 2 :vec3 Normal
		glBindBuffer(GL_ARRAY_BUFFER, nVBO);
		glVertexAttribPointer(2,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)offset[2]);
		offset[2] += normals_size[i] * sizeof(vec3);

		int vertexIDoffset = 0;//glVertexID's offset 
		string mtlname;//material name
		vec3 Ks = vec3(1, 1, 1);//because .mtl excluding specular , so give it here.
		for (int j = 0; j <mtls[i].size(); j++) {//
			mtlname = mtls[i][j];
			//find the material diffuse color in map:KDs by material name.
			glUniform3fv(M_KdID, 1, &KDs[mtlname][0]);
			glUniform3fv(M_KsID, 1, &Ks[0]);
			//          (primitive   , glVertexID base , vertex count    )
			glDrawArrays(GL_TRIANGLES, vertexIDoffset, triangleFaces[i][j + 1] * 3);
			//we draw triangles by giving the glVertexID base and vertex count is face count*3
			vertexIDoffset += triangleFaces[i][j + 1] * 3;//glVertexID's base offset is face count*3
		}//end for loop for draw one part of the robot	

	}//end for loop for updating and drawing model
	
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}

// Load models to screen
void updateModels()
{
	// Set all matrix to identity matrix
	for (int i = 0; i < PARTSNUM; i++) 
	{
		models[i] = mat4(1.0f);
		rotation[i] = mat4(1.0f);
		translation[i] = mat4(1.0f);
	}
	
	// Body===========================================================
	rotation[BODY] = rotate(modelAngle[BODY].X, 1, 0, 0) *
		rotate(modelAngle[BODY].Y, 0, 1, 0) *
		rotate(modelAngle[BODY].Z, 0, 0, 1);
	translation[BODY] = translate(bodyPosition[0], bodyPosition[1], bodyPosition[2]);
	models[BODY] = translation[BODY] * rotation[BODY];
	//=============================================================
	// Head===========================================================
	rotation[HEAD] = rotate(modelAngle[HEAD].X, 1, 0, 0) *
		rotate(modelAngle[HEAD].Y, 0, 1, 0) *
		rotate(modelAngle[HEAD].Z, 0, 0, 1);
	translation[HEAD] = translate(0, 0.8445, 0.0596);// translate form body to neck
	models[HEAD] = models[BODY] * translation[HEAD] * rotation[HEAD];
	//=============================================================
	// Left Arm=======================================================
	// Left Upper Arm
	rotation[LEFTUPPERARM] = rotate(modelAngle[LEFTUPPERARM].X, 1, 0, 0) *
		rotate(modelAngle[LEFTUPPERARM].Y, 0, 1, 0) *
		rotate(modelAngle[LEFTUPPERARM].Z, 0, 0, 1);
	translation[LEFTUPPERARM] = translate(1.2600, 0.0105, -0.0979);// translate form body to left shoulder
	models[LEFTUPPERARM] = models[BODY] * translation[LEFTUPPERARM] * rotation[LEFTUPPERARM];
	// Left Lower Arm
	rotation[LEFTLOWERARM] = rotate(modelAngle[LEFTLOWERARM].X, 1, 0, 0) *
		rotate(modelAngle[LEFTLOWERARM].Y, 0, 1, 0) *
		rotate(modelAngle[LEFTLOWERARM].Z, 0, 0, 1);
	translation[LEFTLOWERARM] = translate(0.1692, -1.6185, -0.1509);// translate form leftUpperArm to leftLowerArm
	models[LEFTLOWERARM] = models[LEFTUPPERARM] * translation[LEFTLOWERARM] * rotation[LEFTLOWERARM];
	// Left Hand
	rotation[LEFTHAND] = rotate(modelAngle[LEFTHAND].X, 1, 0, 0) *
		rotate(modelAngle[LEFTHAND].Y, 0, 1, 0) *
		rotate(modelAngle[LEFTHAND].Z, 0, 0, 1);
	translation[LEFTHAND] = translate(-0.0441, -1.4675, 0.4421);// translate form leftLower to leftHand
	models[LEFTHAND] = models[LEFTLOWERARM] * translation[LEFTHAND] * rotation[LEFTHAND];
	//=============================================================
	// Right Arm======================================================
	// Right Upper Arm
	rotation[RIGHTUPPERARM] = rotate(modelAngle[RIGHTUPPERARM].X, 1, 0, 0) *
		rotate(modelAngle[RIGHTUPPERARM].Y, 0, 1, 0) *
		rotate(modelAngle[RIGHTUPPERARM].Z, 0, 0, 1);
	translation[RIGHTUPPERARM] = translate(-1.2603, 0.0295, -0.0982);// translate form body to right shoulder
	models[RIGHTUPPERARM] = models[BODY] * translation[RIGHTUPPERARM] * rotation[RIGHTUPPERARM];
	// Right Lower Arm
	rotation[RIGHTLOWERARM] = rotate(modelAngle[RIGHTLOWERARM].X, 1, 0, 0) *
		rotate(modelAngle[RIGHTLOWERARM].Y, 0, 1, 0) *
		rotate(modelAngle[RIGHTLOWERARM].Z, 0, 0, 1);
	translation[RIGHTLOWERARM] = translate(-0.1609, -1.6508, -0.1549);// translate form rightUpperArm to rightLowerArm
	models[RIGHTLOWERARM] = models[RIGHTUPPERARM] * translation[RIGHTLOWERARM] * rotation[RIGHTLOWERARM];
	// Right Hand
	rotation[RIGHTHAND] = rotate(modelAngle[RIGHTHAND].X, 1, 0, 0) *
		rotate(modelAngle[RIGHTHAND].Y, 0, 1, 0) *
		rotate(modelAngle[RIGHTHAND].Z, 0, 0, 1);
	translation[RIGHTHAND] = translate(0.0336, -1.4521, 0.4654);// translate form rightLower to rightHand
	models[RIGHTHAND] = models[RIGHTLOWERARM] * translation[RIGHTHAND] * rotation[RIGHTHAND];
	//=============================================================
	// Left Leg=======================================================
	// Left Thigh
	rotation[LEFTTHIGH] = rotate(modelAngle[LEFTTHIGH].X, 1, 0, 0) *
		rotate(modelAngle[LEFTTHIGH].Y, 0, 1, 0) *
		rotate(modelAngle[LEFTTHIGH].Z, 0, 0, 1);
	translation[LEFTTHIGH] = translate(0.4237, -2.8345, -0.0082);// translate form body to leftThigh
	models[LEFTTHIGH] = models[BODY] * translation[LEFTTHIGH] * rotation[LEFTTHIGH];
	// Left Shank
	rotation[LEFTSHANK] = rotate(modelAngle[LEFTSHANK].X, 1, 0, 0) *
		rotate(modelAngle[LEFTSHANK].Y, 0, 1, 0) *
		rotate(modelAngle[LEFTSHANK].Z, 0, 0, 1);
	translation[LEFTSHANK] = translate(-0.0102, -2.5548, -0.1870);// translate form leftThigh to leftShank
	models[LEFTSHANK] = models[LEFTTHIGH] * translation[LEFTSHANK] * rotation[LEFTSHANK];
	// Left Foot
	rotation[LEFTFOOT] = rotate(modelAngle[LEFTFOOT].X, 1, 0, 0) *
		rotate(modelAngle[LEFTFOOT].Y, 0, 1, 0) *
		rotate(modelAngle[LEFTFOOT].Z, 0, 0, 1);
	translation[LEFTFOOT] = translate(-0.1048, -2.4946, -0.2229);// translate form leftShank to leftFoot
	models[LEFTFOOT] = models[LEFTSHANK] * translation[LEFTFOOT] * rotation[LEFTFOOT];
	//=============================================================
	// Right Leg======================================================
	// Right Thigh
	rotation[RIGHTTHIGH] = rotate(modelAngle[RIGHTTHIGH].X, 1, 0, 0) *
		rotate(modelAngle[RIGHTTHIGH].Y, 0, 1, 0) *
		rotate(modelAngle[RIGHTTHIGH].Z, 0, 0, 1);
	translation[RIGHTTHIGH] = translate(-0.4244, -2.8450, -0.0082);// translate form body to rightThigh
	models[RIGHTTHIGH] = models[BODY] * translation[RIGHTTHIGH] * rotation[RIGHTTHIGH];
	// Right Shank
	rotation[RIGHTSHANK] = rotate(modelAngle[RIGHTSHANK].X, 1, 0, 0) *
		rotate(modelAngle[RIGHTSHANK].Y, 0, 1, 0) *
		rotate(modelAngle[RIGHTSHANK].Z, 0, 0, 1);
	translation[RIGHTSHANK] = translate(0.0103, -2.5548, -0.1870);// translate form rightThigh to rightShank
	models[RIGHTSHANK] = models[RIGHTTHIGH] * translation[RIGHTSHANK] * rotation[RIGHTSHANK];
	// Right Foot
	rotation[RIGHTFOOT] = rotate(modelAngle[RIGHTFOOT].X, 1, 0, 0) *
		rotate(modelAngle[RIGHTFOOT].Y, 0, 1, 0) *
		rotate(modelAngle[RIGHTFOOT].Z, 0, 0, 1);
	translation[RIGHTFOOT] = translate(0.1048, -2.4946, -0.2229);// translate form rightShank to rightFoot
	models[RIGHTFOOT] = models[RIGHTSHANK] * translation[RIGHTFOOT] * rotation[RIGHTFOOT];
	//=============================================================
}

// Translate model's position
mat4 translate(float x, float y, float z)
{
	vec4 t = vec4(x, y, z, 1);
	vec4 c1 = vec4(1, 0, 0, 0);
	vec4 c2 = vec4(0, 1, 0, 0);
	vec4 c3 = vec4(0, 0, 1, 0);
	mat4 M = mat4(c1, c2, c3, t);
	return M;
}

// Scale the model
mat4 scale(float x, float y, float z)
{
	vec4 c1 = vec4(x, 0, 0, 0);
	vec4 c2 = vec4(0, y, 0, 0);
	vec4 c3 = vec4(0, 0, z, 0);
	vec4 c4 = vec4(0, 0, 0, 1);
	mat4 M = mat4(c1, c2, c3, c4);
	return M;
}

// Rotate the model
mat4 rotate(float angle, float x, float y, float z)
{
	float r = DOR(angle);
	mat4 M = mat4(1);

	vec4 c1 = vec4(cos(r) + (1 - cos(r))*x*x, (1 - cos(r))*y*x + sin(r)*z, (1 - cos(r))*z*x - sin(r)*y, 0);
	vec4 c2 = vec4((1 - cos(r))*y*x - sin(r)*z, cos(r) + (1 - cos(r))*y*y, (1 - cos(r))*z*y + sin(r)*x, 0);
	vec4 c3 = vec4((1 - cos(r))*z*x + sin(r)*y, (1 - cos(r))*z*y - sin(r)*x, cos(r) + (1 - cos(r))*z*z, 0);
	vec4 c4 = vec4(0, 0, 0, 1);
	M = mat4(c1, c2, c3, c4);
	return M;
}

// Change size function
void ChangeSize(int w, int h)
{
	if (h == 0)
		h = 1;

	glViewport(0, 0, w, h);
	Projection = perspective(80.0f, (float)w / h, 0.1f, 100.0f);

	winWidth = w;
	winHeight = h;
}

// Keyboard Part
// Keyboard function
void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'w':
	case 'W':
		eyedistance -= 0.2;
		break;
	case 's':
	case 'S':
		eyedistance += 0.2;
		break;
	case 'a':
	case 'A':
		eyeAngley -= 10;
		break;
	case 'd':
	case 'D':
		eyeAngley += 10;
		break;
	case 'r':
	case 'R':
		modelAngle[LEFTUPPERARM].X -= 5;
		if (modelAngle[LEFTUPPERARM].X == -360)
			modelAngle[LEFTUPPERARM].X = 0;
		movey = 0;
		movex = 0;
		break;
	case 't':
	case 'T':
		modelAngle[LEFTLOWERARM].X -= 5;
		if (modelAngle[LEFTLOWERARM].X == -360)
			modelAngle[LEFTLOWERARM].X = 0;
		movey = 0;
		movex = 0;
		break;
	case 'q':
	case 'Q':
		lookDistance--;
		break;
	case 'e':
	case 'E':
		lookDistance++;
		break;
	case 'f':
	case 'F':
		glutFullScreenToggle();
		break;
	}
	glutPostRedisplay();
}

void Special(int key, int x, int y) {
	switch(key) {
		case GLUT_KEY_F1:
			stopAutoRun = false;
			glutTimerFunc(autoRunInterval, autoRun, 0);
			break;
		case GLUT_KEY_F2:
			stopAutoRun = true;
			break;
	}

	return;
}

// Mouse Part
// Mouse function
void Mouse(int button, int state, int x, int y)
{
	if (button == 2) isFrame = false;
}

// Motion function
void motion(int x, int y)
{
	mouseX = x;
	mouseY = y;
}

// Timer Part
// Timer function
void idle(int dummy)
{
	if (lastAction != action)
		dummy = 0;
	lastAction = action;

	isFrame = true;
	int out = 0;

	// ATEASE
	if (action == ATEASE)
	{
		atEase(dummy);
		out = dummy + 1;
		interval = 100;
	}
	// SALUTE
	else if (action == SALUTE)
	{
		salute(dummy);
		out = dummy + 1;
		interval = 25;
	}
	// WALK
	else if (action == WALK)
	{
		walk(dummy);
		out = dummy + 1;
		// Run only one time 0
		if (out > 12)
			out = 1;
		interval = 100;
	}
	// RUN
	else if (action == RUN)
	{
		run(dummy);
		out = dummy + 1;
		// Run only one time 0
		if (out > 12)
			out = 1;
		interval = 100;
	}
	// SQUATS
	else if (action == SQUATS)
	{
		squats(dummy);
		out = dummy + 1;
		if (out > 23)
			out = 0;
		interval = 25;
	}
	// JUMP
	else if (action == JUMP) {
		jump(dummy);
		out = dummy + 1;
		if (out > 23)
			out = 0;
		interval = 100;
	}
	// PETANQUE (fa shi gun qiu)
	else if (action == PETANQUE) {
		petanque(dummy);
		out = dummy + 1;
		if (out > 38)
			out = 9;
		interval = 100;
	}
	// LOSE
	else if (action == LOSE)
	{
		lose(dummy);
		out = dummy + 1;
		interval = 100;
	}
	// BREAKINGKS
	else if (action == BREAKINGKS)
	{
		breakingKS(dummy);
		out = dummy + 1;
		if (out > 54)
			out = 7;
		interval = 50;
	}
	// BREAKINGICE
	else if (action == BREAKINGICE)
	{
		breakingICE(dummy);
		out = dummy + 1;
		interval = 50;
	}
	// LOCKINGTWIRL
	else if (action == LOCKINGTWIRL)
	{
		lockingWT(dummy);
		out = dummy + 1;
		if (out > 41)
			out = 0;
		interval = 100;
	}
	// LOCHINGSCOOBA
	else if (action == LOCHINGSCOOBA)
	{
		lockingSH(dummy);
		out = dummy + 1;
		interval = 30;
	}
	// ATTENTION
	else if (action == ATTENTION)
	{
		resetObj(dummy);
		out = 0;
	}

	glutPostRedisplay();
	glutTimerFunc(interval, idle, out);
}

void autoRun(int eventNo) {
	if (!prepared4AutoRun) {
		glutTimerFunc(autoRunInterval, autoRun, eventNo);
		return;
	}

	const int ACTION_TOTAL_NUM = 13;
	const int SCENE_TOTAL_NUM = 12;
	const int SHADER_TOTAL_NUM = 6;

	int actionChoice = eventNo % ACTION_TOTAL_NUM;
	int sceneChoice = (eventNo % SCENE_TOTAL_NUM == 1 ? 2 : eventNo) % SCENE_TOTAL_NUM;
	int shaderChoice = eventNo % SHADER_TOTAL_NUM;

	ActionMenuEvents(actionChoice);
	SceneMenuEvents(sceneChoice);
	ShaderMenuEvents(shaderChoice);

	if(!stopAutoRun)
		glutTimerFunc(autoRunInterval, autoRun, eventNo + 1);

	return;
}

// Reset the model
void resetObj(int frame)
{
	for (int i = 0; i < PARTSNUM; i++)
	{
		//modelAngle[i].angle = 0;
		modelAngle[i].X = 0;
		modelAngle[i].Y = 0;
		modelAngle[i].Z = 0;
	}

	bodyPosition[0] = bodyPosition[1] = bodyPosition[2] = 0;
}

// At Ease
void atEase(int frame)
{
	switch (frame)
	{
		// Initial the angle of lowerArm and Shank
	case 0:
		// ARM
		modelAngle[LEFTUPPERARM].Y -= 90;
		modelAngle[RIGHTUPPERARM].Y += 90;
		break;
	case 1:
		// ARM
		modelAngle[LEFTUPPERARM].Z -= 10;
		modelAngle[RIGHTUPPERARM].Z += 10;
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
		// ARM
		modelAngle[LEFTLOWERARM].X -= 5;
		modelAngle[RIGHTLOWERARM].X -= 5;
		// LEG
		modelAngle[LEFTTHIGH].Z += 2.5;
		modelAngle[RIGHTTHIGH].Z -= 2.5;

		bodyPosition[1] -= 0.05;
		bodyPosition[0] -= 0.25;
		break;
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
	case 13:
		break;
	case 14:
	case 15:
	case 16:
	case 17:
	case 18:
	case 19:
		// ARM
		modelAngle[LEFTLOWERARM].X += 5;
		modelAngle[RIGHTLOWERARM].X += 5;
		// LEG
		modelAngle[LEFTTHIGH].Z -= 2.5;
		modelAngle[RIGHTTHIGH].Z += 2.5;

		bodyPosition[1] += 0.05;
		bodyPosition[0] += 0.25;
		break;
	case 20:
		// ARM
		modelAngle[LEFTUPPERARM].Z += 10;
		modelAngle[RIGHTUPPERARM].Z -= 10;
		break;
	case 21:
		// ARM
		modelAngle[LEFTUPPERARM].Y += 90;
		modelAngle[RIGHTUPPERARM].Y -= 90;
		break;
	}
}

// Salute
void salute(int frame)
{
	switch (frame)
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
		// ARM
		modelAngle[RIGHTUPPERARM].Z -= 15;
		// LEG
		modelAngle[LEFTTHIGH].Z += 3;
		break;
	case 6:
		// ARM
		modelAngle[RIGHTLOWERARM].X -= 25;
		modelAngle[RIGHTHAND].Y -= 7;
		// LEG
		modelAngle[LEFTTHIGH].Z -= 1.5;
		break;
	case 7:
		// ARM
		modelAngle[RIGHTLOWERARM].Z -= 5;
		// LEG
		modelAngle[LEFTTHIGH].Z -= 1.5;
		break;
	case 8:
		// ARM
		modelAngle[RIGHTLOWERARM].X -= 25;
		modelAngle[RIGHTHAND].Y -= 7;
		// LEG
		modelAngle[LEFTTHIGH].Z -= 1.5;
		break;
	case 9:
		// ARM
		modelAngle[RIGHTLOWERARM].Z -= 5;
		// LEG
		modelAngle[LEFTTHIGH].Z -= 1.5;
		break;
	case 10:
		// ARM
		modelAngle[RIGHTLOWERARM].X -= 25;
		modelAngle[RIGHTHAND].Y -= 7;
		// LEG
		modelAngle[LEFTTHIGH].Z -= 1.5;
		break;
	case 11:
		// ARM
		modelAngle[RIGHTLOWERARM].Z -= 5;
		// LEG
		modelAngle[LEFTTHIGH].Z -= 1.5;
		break;
	case 12:
		// ARM
		modelAngle[RIGHTLOWERARM].X -= 25;
		modelAngle[RIGHTHAND].Y -= 7;
		// LEG
		modelAngle[LEFTTHIGH].Z -= 1.5;
		break;
	case 13:
		// ARM
		modelAngle[RIGHTLOWERARM].Z -= 5;
		// LEG
		modelAngle[LEFTTHIGH].Z -= 1.5;
		break;
	case 14:
		// ARM
		modelAngle[RIGHTLOWERARM].X -= 25;
		modelAngle[RIGHTHAND].Y -= 7;
		// LEG
		modelAngle[LEFTTHIGH].Z -= 1.5;
		break;
	case 15:
		// ARM
		modelAngle[RIGHTLOWERARM].Z -= 5;
		// LEG
		modelAngle[LEFTTHIGH].Z -= 1.5;
		break;
	case 16:
		// ARM
		modelAngle[RIGHTLOWERARM].X -= 25;
		modelAngle[RIGHTHAND].Y -= 7;
		// LEG
		modelAngle[LEFTTHIGH].Z -= 1.5;
		break;
	case 17:
		// ARM
		modelAngle[RIGHTLOWERARM].Z -= 5;
		// LEG
		modelAngle[LEFTTHIGH].Z -= 1.5;
		break;
	case 18:
	case 19:
	case 20:
	case 21:
	case 22:
	case 23:
		break;
	case 24:
		modelAngle[RIGHTUPPERARM].Z += 15;
		modelAngle[RIGHTLOWERARM].X += 50;
		modelAngle[RIGHTHAND].Y += 7;
		break;
	case 25:
		modelAngle[RIGHTUPPERARM].Z += 15;
		modelAngle[RIGHTLOWERARM].Z += 10;
		modelAngle[RIGHTHAND].Y += 7;
		break;
	case 26:
		modelAngle[RIGHTUPPERARM].Z += 15;
		modelAngle[RIGHTLOWERARM].X += 50;
		modelAngle[RIGHTHAND].Y += 7;
		break;
	case 27:
		modelAngle[RIGHTUPPERARM].Z += 15;
		modelAngle[RIGHTLOWERARM].Z += 10;
		modelAngle[RIGHTHAND].Y += 7;
		break;
	case 28:
		modelAngle[RIGHTUPPERARM].Z += 15;
		modelAngle[RIGHTLOWERARM].X += 50;
		modelAngle[RIGHTHAND].Y += 7;
		break;
	case 29:
		modelAngle[RIGHTUPPERARM].Z += 15;
		modelAngle[RIGHTLOWERARM].Z += 10;
		modelAngle[RIGHTHAND].Y += 7;
		break;
	}
}

// Walking
void walk(int frame) {
	switch (frame)
	{
		// Initial the angle of lowerArm and Shank
	case 0:
		modelAngle[LEFTLOWERARM].X = 0;
		modelAngle[RIGHTLOWERARM] = modelAngle[LEFTLOWERARM];
		modelAngle[LEFTSHANK].X = 0;
		modelAngle[RIGHTSHANK] = modelAngle[LEFTSHANK];
		break;
	case 1:
	case 2:
	case 3:
		// ARM
		modelAngle[LEFTUPPERARM].X += 5;
		modelAngle[RIGHTUPPERARM].X -= 5;
		// LEG
		modelAngle[LEFTTHIGH].X -= 10;
		modelAngle[RIGHTTHIGH].X += 10;
		// SHANK
		modelAngle[LEFTSHANK].X += 10;
		modelAngle[RIGHTFOOT].X += 3;

		bodyPosition[1] += 0.05;
		break;
	case 4:
	case 5:
	case 6:
		// ARM
		modelAngle[LEFTUPPERARM].X -= 5;
		modelAngle[RIGHTUPPERARM].X += 5;
		// LEG
		modelAngle[LEFTTHIGH].X += 10;
		modelAngle[RIGHTTHIGH].X -= 10;
		// SHANK
		modelAngle[LEFTSHANK].X -= 10;
		modelAngle[RIGHTFOOT].X -= 3;

		bodyPosition[1] -= 0.05;
		break;
	case 7:
	case 8:
	case 9:
		// ARM
		modelAngle[LEFTUPPERARM].X -= 5;
		modelAngle[RIGHTUPPERARM].X += 5;
		// LEG
		modelAngle[LEFTTHIGH].X += 10;
		modelAngle[RIGHTTHIGH].X -= 10;
		// SHANK
		modelAngle[RIGHTSHANK].X += 10;
		modelAngle[LEFTFOOT].X += 3;
		/*modelAngle[LEFTSHANK].X = 0;
		modelAngle[RIGHTSHANK].X = 0;*/
		bodyPosition[1] += 0.05;
		break;
	case 10:
	case 11:
	case 12:
		// ARM
		modelAngle[LEFTUPPERARM].X += 5;
		modelAngle[RIGHTUPPERARM].X -= 5;
		// LEG
		modelAngle[LEFTTHIGH].X -= 10;
		modelAngle[RIGHTTHIGH].X += 10;
		// SHANK
		modelAngle[RIGHTSHANK].X -= 10;
		modelAngle[LEFTFOOT].X -= 3;

		bodyPosition[1] -= 0.05;
		break;
	}
}

// Running
void run(int frame) {
	switch (frame)
	{
		// Initial the angle of lowerArm and Shank
	case 0:
		modelAngle[LEFTLOWERARM].X = -45;
		modelAngle[RIGHTLOWERARM] = modelAngle[LEFTLOWERARM];
		modelAngle[LEFTSHANK].X = 0;
		modelAngle[RIGHTSHANK] = modelAngle[LEFTSHANK];
		break;
	case 1:
	case 2:
	case 3:
		// ARM
		modelAngle[LEFTUPPERARM].X += 15;
		modelAngle[RIGHTUPPERARM].X -= 15;
		// LEG
		modelAngle[LEFTTHIGH].X -= 15;
		modelAngle[RIGHTTHIGH].X += 15;
		// SHANK
		modelAngle[LEFTSHANK].X += 15;
		modelAngle[RIGHTFOOT].X += 5;

		bodyPosition[1] += 0.2;
		break;
	case 4:
	case 5:
	case 6:
		// ARM
		modelAngle[LEFTUPPERARM].X -= 15;
		modelAngle[RIGHTUPPERARM].X += 15;
		// LEG
		modelAngle[LEFTTHIGH].X += 15;
		modelAngle[RIGHTTHIGH].X -= 15;
		// SHANK
		modelAngle[LEFTSHANK].X -= 15;
		modelAngle[RIGHTFOOT].X -= 5;

		bodyPosition[1] -= 0.2;
		break;
	case 7:
	case 8:
	case 9:
		// ARM
		modelAngle[LEFTUPPERARM].X -= 15;
		modelAngle[RIGHTUPPERARM].X += 15;
		// LEG
		modelAngle[LEFTTHIGH].X += 15;
		modelAngle[RIGHTTHIGH].X -= 15;
		// SHANK
		modelAngle[RIGHTSHANK].X += 15;
		modelAngle[LEFTFOOT].X += 5;

		bodyPosition[1] += 0.2;
		break;
	case 10:
	case 11:
	case 12:
		// ARM
		modelAngle[LEFTUPPERARM].X += 15;
		modelAngle[RIGHTUPPERARM].X -= 15;
		// LEG
		modelAngle[LEFTTHIGH].X -= 15;
		modelAngle[RIGHTTHIGH].X += 15;
		// SHANK
		modelAngle[RIGHTSHANK].X -= 15;
		modelAngle[LEFTFOOT].X -= 5;

		bodyPosition[1] -= 0.2;
		break;
	}
}

// Squarting
void squats(int frame)
{
	switch (frame)
	{
	case 0:
		modelAngle[LEFTTHIGH].Z += 5;
		modelAngle[RIGHTTHIGH].Z -= 5;
		break;
	case 1:
		modelAngle[LEFTTHIGH].Y += 5;
		modelAngle[RIGHTTHIGH].Y -= 5;

		modelAngle[LEFTUPPERARM].Y -= 3;
		modelAngle[RIGHTUPPERARM].Y -= 3;
		break;
	case 2:
		modelAngle[LEFTTHIGH].Z += 5;
		modelAngle[RIGHTTHIGH].Z -= 5;
		break;
	case 3:
		modelAngle[LEFTTHIGH].X -= 34;
		modelAngle[LEFTSHANK].X += 56;
		modelAngle[LEFTFOOT].X -= 30;

		modelAngle[RIGHTTHIGH].X -= 34;
		modelAngle[RIGHTSHANK].X += 56;
		modelAngle[RIGHTFOOT].X -= 30;

		modelAngle[LEFTUPPERARM].X -= 10;
		modelAngle[RIGHTUPPERARM].X -= 10;
		bodyPosition[1] -= 0.65;
		break;
	case 4:
		modelAngle[LEFTTHIGH].Z += 5;
		modelAngle[RIGHTTHIGH].Z -= 5;
		break;
	case 5:
		modelAngle[LEFTTHIGH].Y += 5;
		modelAngle[RIGHTTHIGH].Y -= 5;

		modelAngle[LEFTUPPERARM].Y -= 3;
		modelAngle[RIGHTUPPERARM].Y -= 3;
		break;
	case 6:
		modelAngle[LEFTTHIGH].Z += 5;
		modelAngle[RIGHTTHIGH].Z -= 5;
		break;
	case 7:
		modelAngle[LEFTTHIGH].X -= 34;
		modelAngle[LEFTSHANK].X += 56;
		modelAngle[LEFTFOOT].X -= 30;

		modelAngle[RIGHTTHIGH].X -= 34;
		modelAngle[RIGHTSHANK].X += 56;
		modelAngle[RIGHTFOOT].X -= 30;

		modelAngle[LEFTUPPERARM].X -= 10;
		modelAngle[RIGHTUPPERARM].X -= 10;
		bodyPosition[1] -= 0.65;
		break;
	case 8:
		modelAngle[LEFTTHIGH].Z += 5;
		modelAngle[RIGHTTHIGH].Z -= 5;
		break;
	case 9:
		modelAngle[LEFTTHIGH].Y += 5;
		modelAngle[RIGHTTHIGH].Y -= 5;

		modelAngle[LEFTUPPERARM].Y -= 3;
		modelAngle[RIGHTUPPERARM].Y -= 3;
		break;
	case 10:
		modelAngle[LEFTTHIGH].Z += 5;
		modelAngle[RIGHTTHIGH].Z -= 5;
		break;
	case 11:
		modelAngle[LEFTTHIGH].X -= 34;
		modelAngle[LEFTSHANK].X += 56;
		modelAngle[LEFTFOOT].X -= 30;

		modelAngle[RIGHTTHIGH].X -= 34;
		modelAngle[RIGHTSHANK].X += 56;
		modelAngle[RIGHTFOOT].X -= 30;

		modelAngle[LEFTUPPERARM].X -= 10;
		modelAngle[RIGHTUPPERARM].X -= 10;
		bodyPosition[1] -= 0.65;
		break;
	case 12:
		modelAngle[LEFTTHIGH].Z -= 5;
		modelAngle[RIGHTTHIGH].Z += 5;
		break;
	case 13:
		modelAngle[LEFTTHIGH].Y -= 5;
		modelAngle[RIGHTTHIGH].Y += 5;

		modelAngle[LEFTUPPERARM].Y += 3;
		modelAngle[RIGHTUPPERARM].Y += 3;
		break;
	case 14:
		modelAngle[LEFTTHIGH].Z -= 5;
		modelAngle[RIGHTTHIGH].Z += 5;
		break;
	case 15:
		modelAngle[LEFTTHIGH].X += 34;
		modelAngle[LEFTSHANK].X -= 56;
		modelAngle[LEFTFOOT].X += 30;

		modelAngle[RIGHTTHIGH].X += 34;
		modelAngle[RIGHTSHANK].X -= 56;
		modelAngle[RIGHTFOOT].X += 30;

		modelAngle[LEFTUPPERARM].X += 10;
		modelAngle[RIGHTUPPERARM].X += 10;
		bodyPosition[1] += 0.65;
		break;
	case 16:
		modelAngle[LEFTTHIGH].Z -= 5;
		modelAngle[RIGHTTHIGH].Z += 5;
		break;
	case 17:
		modelAngle[LEFTTHIGH].Y -= 5;
		modelAngle[RIGHTTHIGH].Y += 5;

		modelAngle[LEFTUPPERARM].Y += 3;
		modelAngle[RIGHTUPPERARM].Y += 3;
		break;
	case 18:
		modelAngle[LEFTTHIGH].Z -= 5;
		modelAngle[RIGHTTHIGH].Z += 5;
		break;
	case 19:
		modelAngle[LEFTTHIGH].X += 34;
		modelAngle[LEFTSHANK].X -= 56;
		modelAngle[LEFTFOOT].X += 30;

		modelAngle[RIGHTTHIGH].X += 34;
		modelAngle[RIGHTSHANK].X -= 56;
		modelAngle[RIGHTFOOT].X += 30;

		modelAngle[LEFTUPPERARM].X += 10;
		modelAngle[RIGHTUPPERARM].X += 10;
		bodyPosition[1] += 0.65;
		break;
	case 20:
		modelAngle[LEFTTHIGH].Z -= 5;
		modelAngle[RIGHTTHIGH].Z += 5;
		break;
	case 21:
		modelAngle[LEFTTHIGH].Y -= 5;
		modelAngle[RIGHTTHIGH].Y += 5;

		modelAngle[LEFTUPPERARM].Y += 3;
		modelAngle[RIGHTUPPERARM].Y += 3;
		break;
	case 22:
		modelAngle[LEFTTHIGH].Z -= 5;
		modelAngle[RIGHTTHIGH].Z += 5;
		break;
	case 23:
		modelAngle[LEFTTHIGH].X += 34;
		modelAngle[LEFTSHANK].X -= 56;
		modelAngle[LEFTFOOT].X += 30;

		modelAngle[RIGHTTHIGH].X += 34;
		modelAngle[RIGHTSHANK].X -= 56;
		modelAngle[RIGHTFOOT].X += 30;

		modelAngle[LEFTUPPERARM].X += 10;
		modelAngle[RIGHTUPPERARM].X += 10;
		bodyPosition[1] += 0.65;
		break;
	}
	return;
}

// Jump
void jump(int frame) {
	switch (frame) {
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
		modelAngle[LEFTUPPERARM].X += 25;
		modelAngle[RIGHTUPPERARM].X += 25;

		modelAngle[LEFTTHIGH].X -= 17;
		modelAngle[LEFTSHANK].X += 28;
		modelAngle[LEFTFOOT].X -= 15;

		modelAngle[RIGHTTHIGH].X -= 17;
		modelAngle[RIGHTSHANK].X += 28;
		modelAngle[RIGHTFOOT].X -= 15;

		modelAngle[BODY].X += 4;
		bodyPosition[1] -= 0.7;
		break;

	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
		modelAngle[LEFTUPPERARM].X -= 25;
		modelAngle[RIGHTUPPERARM].X -= 25;

		modelAngle[LEFTTHIGH].X += 17;
		modelAngle[LEFTSHANK].X -= 28;
		modelAngle[LEFTFOOT].X += 15;

		modelAngle[RIGHTTHIGH].X += 17;
		modelAngle[RIGHTSHANK].X -= 28;
		modelAngle[RIGHTFOOT].X += 15;

		modelAngle[BODY].X -= 4;
		bodyPosition[1] += 0.7;
		break;

	case 12:
		modelAngle[LEFTUPPERARM].X -= 25;
		modelAngle[RIGHTUPPERARM].X -= 25;

		modelAngle[LEFTTHIGH].Z += 3;
		modelAngle[RIGHTTHIGH].Z -= 3;

		modelAngle[LEFTFOOT].X += 5;
		modelAngle[RIGHTFOOT].X += 5;
		bodyPosition[1] += 0.7;
		break;
	case 13:
		modelAngle[LEFTUPPERARM].X -= 23;
		modelAngle[RIGHTUPPERARM].X -= 23;

		modelAngle[LEFTTHIGH].Z += 2;
		modelAngle[RIGHTTHIGH].Z -= 2;

		modelAngle[LEFTFOOT].X += 5;
		modelAngle[RIGHTFOOT].X += 5;
		bodyPosition[1] += 0.7;
		break;

	case 14:
		modelAngle[LEFTUPPERARM].X -= 21;
		modelAngle[RIGHTUPPERARM].X -= 21;

		modelAngle[LEFTTHIGH].Z += 1;
		modelAngle[RIGHTTHIGH].Z -= 1;
		bodyPosition[1] += 0.7;
		break;
	case 15:
		modelAngle[LEFTUPPERARM].X -= 19;
		modelAngle[RIGHTUPPERARM].X -= 19;

		bodyPosition[1] += 0.5;
		break;
	case 16:
		modelAngle[LEFTUPPERARM].X -= 17;
		modelAngle[RIGHTUPPERARM].X -= 17;

		bodyPosition[1] += 0.3;
		break;
	case 17:
		modelAngle[LEFTUPPERARM].X -= 15;
		modelAngle[RIGHTUPPERARM].X -= 15;

		bodyPosition[1] += 0.1;
		break;

	case 18:
		modelAngle[LEFTUPPERARM].X += 15;
		modelAngle[RIGHTUPPERARM].X += 15;

		bodyPosition[1] -= 0.1;
		break;
	case 19:
		modelAngle[LEFTUPPERARM].X += 17;
		modelAngle[RIGHTUPPERARM].X += 17;

		bodyPosition[1] -= 0.3;
		break;
	case 20:
		modelAngle[LEFTUPPERARM].X += 19;
		modelAngle[RIGHTUPPERARM].X += 19;

		bodyPosition[1] -= 0.5;
		break;
	case 21:
		modelAngle[LEFTUPPERARM].X += 21;
		modelAngle[RIGHTUPPERARM].X += 21;

		modelAngle[LEFTTHIGH].Z -= 1;
		modelAngle[RIGHTTHIGH].Z += 1;
		bodyPosition[1] -= 0.7;
		break;

	case 22:
		modelAngle[LEFTUPPERARM].X += 23;
		modelAngle[RIGHTUPPERARM].X += 23;

		modelAngle[LEFTTHIGH].Z -= 2;
		modelAngle[RIGHTTHIGH].Z += 2;

		modelAngle[LEFTFOOT].X -= 5;
		modelAngle[RIGHTFOOT].X -= 5;
		bodyPosition[1] -= 0.7;
		break;
	case 23:
		modelAngle[LEFTUPPERARM].X += 25;
		modelAngle[RIGHTUPPERARM].X += 25;

		modelAngle[LEFTTHIGH].Z -= 3;
		modelAngle[RIGHTTHIGH].Z += 3;

		modelAngle[LEFTFOOT].X -= 5;
		modelAngle[RIGHTFOOT].X -= 5;
		bodyPosition[1] -= 0.7;
		break;
	}

	return;
}

// Petanque
void petanque(int frame) {
	switch (frame) {
	case 0:
		modelAngle[LEFTUPPERARM].Y = 0;
		modelAngle[LEFTLOWERARM].X = 20;
		break;

	case 1:
	case 2:
		modelAngle[LEFTUPPERARM].Y -= 45;
		break;

	case 3:
		modelAngle[LEFTUPPERARM].X -= 20;
		break;
	case 4:
		modelAngle[LEFTUPPERARM].X -= 18;
		break;
	case 5:
		modelAngle[LEFTUPPERARM].X -= 16;
		break;
	case 6:
		modelAngle[LEFTUPPERARM].X -= 14;
		break;
	case 7:
		modelAngle[LEFTUPPERARM].X -= 12;
		break;
	case 8:
		modelAngle[LEFTUPPERARM].X -= 10;
		break;

		// ===================================

	case 9:
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
	case 16:
		modelAngle[LEFTUPPERARM].X += 10 + ((frame % 9) * 2);

		modelAngle[LEFTTHIGH].X -= 15;
		modelAngle[LEFTSHANK].X += 15;
		modelAngle[LEFTFOOT].X -= 5;
		modelAngle[RIGHTTHIGH].X -= 15;
		modelAngle[RIGHTSHANK].X += 15;
		modelAngle[RIGHTFOOT].X -= 5;
		modelAngle[BODY].X += 5;
		bodyPosition[1] -= 0.7;
		break;

	case 17:
		modelAngle[LEFTUPPERARM].X += 20;
		break;
	case 18:
		modelAngle[LEFTUPPERARM].X += 15;
		break;
	case 19:
		modelAngle[LEFTUPPERARM].X += 10;
		break;

	case 20:
		break;

	case 21:
		modelAngle[LEFTUPPERARM].X -= 10;
		break;
	case 22:
		modelAngle[LEFTUPPERARM].X -= 15;
		break;
	case 23:
		modelAngle[LEFTUPPERARM].X -= 20;
		break;

	case 24:
	case 25:
	case 26:
	case 27:
	case 28:
	case 29:
	case 30:
	case 31:
		modelAngle[LEFTUPPERARM].X -= 24 - ((frame % 24) * 2);

		modelAngle[LEFTTHIGH].X += 15;
		modelAngle[LEFTSHANK].X -= 15;
		modelAngle[LEFTFOOT].X += 5;
		modelAngle[RIGHTTHIGH].X += 15;
		modelAngle[RIGHTSHANK].X -= 15;
		modelAngle[RIGHTFOOT].X += 5;
		modelAngle[BODY].X -= 5;
		bodyPosition[1] += 0.7;
		break;

	case 32:
	case 33:
	case 34:
		modelAngle[LEFTUPPERARM].X -= 24 - ((frame % 24) * 2);
		break;

	case 35:
		break;

	case 36:
		modelAngle[LEFTUPPERARM].X += 4;
		break;
	case 37:
		modelAngle[LEFTUPPERARM].X += 6;
		break;
	case 38:
		modelAngle[LEFTUPPERARM].X += 8;
		break;
	}

	return;
}

// Lose
void lose(int frame) {
	switch (frame) {
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
		modelAngle[LEFTSHANK].X += 18;
		modelAngle[RIGHTSHANK].X += 18;
		bodyPosition[1] -= 0.6;
		bodyPosition[2] += 0.6;
		break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		modelAngle[BODY].X += 18;
		modelAngle[LEFTHAND].X -= 18;
		modelAngle[RIGHTHAND].X -= 18;
		modelAngle[LEFTUPPERARM].X -= 18;
		modelAngle[RIGHTUPPERARM].X -= 18;
		modelAngle[LEFTTHIGH].X -= 18;
		modelAngle[RIGHTTHIGH].X -= 18;
		bodyPosition[1] -= 0.6;
		bodyPosition[2] += 0.6;
		break;
	}
	return;
}

// Breaking-Kick&Step
void breakingKS(int frame) {
	switch (frame) {
	case 0:
		modelAngle[LEFTUPPERARM].Z = 0;
		modelAngle[LEFTUPPERARM].Y = 0;
		modelAngle[LEFTLOWERARM].X = 0;

		modelAngle[RIGHTUPPERARM].Z = 0;
		modelAngle[RIGHTUPPERARM].Y = 0;
		modelAngle[RIGHTLOWERARM].X = 0;

		modelAngle[LEFTTHIGH].X = 0;
		modelAngle[RIGHTTHIGH].X = 0;
		modelAngle[LEFTSHANK].X = 0;
		modelAngle[RIGHTTHIGH].X = 0;
		break;
		// Left Leg lift
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
		modelAngle[LEFTUPPERARM].Z += 15;
		modelAngle[LEFTLOWERARM].X -= 20;

		modelAngle[RIGHTUPPERARM].Z -= 15;
		modelAngle[RIGHTLOWERARM].X -= 20;

		modelAngle[LEFTTHIGH].X -= 7.5;
		modelAngle[LEFTSHANK].X += 15;

		break;
		// Left Leg kick
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
		modelAngle[LEFTUPPERARM].Y -= 15;
		modelAngle[LEFTLOWERARM].X += 20;

		modelAngle[RIGHTUPPERARM].Y += 15;
		modelAngle[RIGHTLOWERARM].X += 20;

		modelAngle[LEFTSHANK].X -= 15;
		break;
		// Left Leg put in
	case 13:
	case 14:
	case 15:
	case 16:
	case 17:
	case 18:
		modelAngle[LEFTUPPERARM].Y += 15;
		modelAngle[LEFTLOWERARM].X -= 20;

		modelAngle[RIGHTUPPERARM].Y -= 15;
		modelAngle[RIGHTLOWERARM].X -= 20;

		modelAngle[LEFTTHIGH].X += 7.5;
		break;
		// Left Leg step
	case 19:
	case 20:
	case 21:
	case 22:
	case 23:
	case 24:
		modelAngle[LEFTLOWERARM].X += 20;
		modelAngle[RIGHTLOWERARM].X += 20;

		modelAngle[LEFTTHIGH].Z += 3.5;
		modelAngle[RIGHTTHIGH].Z -= 3.5;
		bodyPosition[0] -= 0.3;
		break;
		// Left Leg put in & Right Leg lift
	case 25:
		modelAngle[LEFTLOWERARM].X -= 20;
		modelAngle[RIGHTLOWERARM].X -= 20;
		modelAngle[RIGHTTHIGH].X -= 15;
		modelAngle[RIGHTSHANK].X += 30;
		bodyPosition[0] += 0.3;
		break;
	case 26:
		modelAngle[LEFTLOWERARM].X -= 20;
		modelAngle[RIGHTLOWERARM].X -= 20;
		modelAngle[LEFTTHIGH].Z -= 7;
		modelAngle[RIGHTTHIGH].Z += 7;
		bodyPosition[0] += 0.3;
		break;
	case 27:
		modelAngle[LEFTLOWERARM].X -= 20;
		modelAngle[RIGHTLOWERARM].X -= 20;
		modelAngle[RIGHTTHIGH].X -= 15;
		modelAngle[RIGHTSHANK].X += 30;
		bodyPosition[0] += 0.3;
		break;
	case 28:
		modelAngle[LEFTLOWERARM].X -= 20;
		modelAngle[RIGHTLOWERARM].X -= 20;
		modelAngle[LEFTTHIGH].Z -= 7;
		modelAngle[RIGHTTHIGH].Z += 7;
		bodyPosition[0] += 0.3;
		break;
	case 29:
		modelAngle[LEFTLOWERARM].X -= 20;
		modelAngle[RIGHTLOWERARM].X -= 20;
		modelAngle[RIGHTTHIGH].X -= 15;
		modelAngle[RIGHTSHANK].X += 30;
		bodyPosition[0] += 0.3;
		break;
	case 30:
		modelAngle[LEFTLOWERARM].X -= 20;
		modelAngle[RIGHTLOWERARM].X -= 20;

		modelAngle[LEFTTHIGH].Z -= 7;
		modelAngle[RIGHTTHIGH].Z += 7;
		bodyPosition[0] += 0.3;
		break;
		// Right Leg kick
	case 31:
	case 32:
	case 33:
	case 34:
	case 35:
	case 36:
		modelAngle[LEFTUPPERARM].Y -= 15;
		modelAngle[LEFTLOWERARM].X += 20;

		modelAngle[RIGHTUPPERARM].Y += 15;
		modelAngle[RIGHTLOWERARM].X += 20;

		modelAngle[RIGHTSHANK].X -= 15;
		break;
		// Right Leg put in
	case 37:
	case 38:
	case 39:
	case 40:
	case 41:
	case 42:
		modelAngle[LEFTUPPERARM].Y += 15;
		modelAngle[LEFTLOWERARM].X -= 20;

		modelAngle[RIGHTUPPERARM].Y -= 15;
		modelAngle[RIGHTLOWERARM].X -= 20;

		modelAngle[RIGHTTHIGH].X += 7.5;
		break;
		// Right Leg step
	case 43:
	case 44:
	case 45:
	case 46:
	case 47:
	case 48:
		modelAngle[LEFTLOWERARM].X += 20;
		modelAngle[RIGHTLOWERARM].X += 20;

		modelAngle[LEFTTHIGH].Z += 3.5;
		modelAngle[RIGHTTHIGH].Z -= 3.5;
		bodyPosition[0] += 0.3;
		break;
		// Right Leg put in & Left Leg lift
	case 49:
		modelAngle[LEFTLOWERARM].X -= 20;
		modelAngle[RIGHTLOWERARM].X -= 20;
		modelAngle[LEFTTHIGH].X -= 15;
		modelAngle[LEFTSHANK].X += 30;
		bodyPosition[0] -= 0.3;
		break;
	case 50:
		modelAngle[LEFTLOWERARM].X -= 20;
		modelAngle[RIGHTLOWERARM].X -= 20;
		modelAngle[LEFTTHIGH].Z -= 7;
		modelAngle[RIGHTTHIGH].Z += 7;
		bodyPosition[0] -= 0.3;
		break;
	case 51:
		modelAngle[LEFTLOWERARM].X -= 20;
		modelAngle[RIGHTLOWERARM].X -= 20;
		modelAngle[LEFTTHIGH].X -= 15;
		modelAngle[LEFTSHANK].X += 30;
		bodyPosition[0] -= 0.3;
		break;
	case 52:
		modelAngle[LEFTLOWERARM].X -= 20;
		modelAngle[RIGHTLOWERARM].X -= 20;
		modelAngle[LEFTTHIGH].Z -= 7;
		modelAngle[RIGHTTHIGH].Z += 7;
		bodyPosition[0] -= 0.3;
		break;
	case 53:
		modelAngle[LEFTLOWERARM].X -= 20;
		modelAngle[RIGHTLOWERARM].X -= 20;
		modelAngle[LEFTTHIGH].X -= 15;
		modelAngle[LEFTSHANK].X += 30;
		bodyPosition[0] -= 0.3;
		break;
	case 54:
		modelAngle[LEFTLOWERARM].X -= 20;
		modelAngle[RIGHTLOWERARM].X -= 20;

		modelAngle[LEFTTHIGH].Z -= 7;
		modelAngle[RIGHTTHIGH].Z += 7;
		bodyPosition[0] -= 0.3;
		break;
	default:
		break;
	}


	return;
}

// Breaking-ICE
void breakingICE(int frame) {
	switch (frame) {
	case 0:
		modelAngle[LEFTUPPERARM].Z = 0;
		modelAngle[LEFTUPPERARM].Y = 0;
		modelAngle[LEFTLOWERARM].X = 0;

		modelAngle[RIGHTUPPERARM].Z = 0;
		modelAngle[RIGHTUPPERARM].Y = 0;
		modelAngle[RIGHTLOWERARM].X = 0;

		modelAngle[LEFTTHIGH].X = 0;
		modelAngle[RIGHTTHIGH].X = 0;
		modelAngle[LEFTSHANK].X = 0;
		modelAngle[RIGHTTHIGH].X = 0;
		break;
		// Straight squart
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
		modelAngle[LEFTTHIGH].X -= 20;
		modelAngle[LEFTSHANK].X += 28;
		modelAngle[LEFTFOOT].X -= 15;

		modelAngle[RIGHTTHIGH].X -= 20;
		modelAngle[RIGHTSHANK].X += 28;
		modelAngle[RIGHTFOOT].X -= 15;

		modelAngle[BODY].X += 5;
		bodyPosition[1] -= 0.65;
		break;
		// Rotate body & hold Arm
	case 7:
		modelAngle[LEFTUPPERARM].X -= 60;
		modelAngle[RIGHTUPPERARM].X += 15;
		break;
	case 8:
	case 9:
	case 10:
		modelAngle[BODY].Z += 7.5;
		modelAngle[LEFTUPPERARM].Z -= 10;
		modelAngle[RIGHTLOWERARM].X -= 30;

		modelAngle[LEFTHAND].X -= 15;
		modelAngle[RIGHTHAND].X -= 15;
		break;
	case 11:
	case 12:
	case 13:
		modelAngle[BODY].Z += 7.5;
		modelAngle[LEFTUPPERARM].Z -= 10;
		modelAngle[RIGHTLOWERARM].Y -= 35;

		modelAngle[LEFTHAND].X -= 15;
		modelAngle[RIGHTHAND].X -= 15;
		break;
		// Rotate body
	case 14:
	case 15:
	case 16:
	case 17:
	case 18:
	case 19:
		modelAngle[BODY].Z += 7.5;
		break;
		// Rotate body & Straight Leg
	case 20:
	case 21:
	case 22:
	case 23:
	case 24:
	case 25:
		modelAngle[BODY].Z += 7.5;
		modelAngle[LEFTTHIGH].X += 20;
		modelAngle[LEFTSHANK].X -= 28;
		modelAngle[LEFTFOOT].X += 15;

		modelAngle[RIGHTTHIGH].X += 20;
		modelAngle[RIGHTSHANK].X -= 28;
		modelAngle[RIGHTFOOT].X += 15;
		break;
		// Stop
	case 26:
	case 27:
	case 28:
	case 29:
	case 30:
	case 31:
		break;
		// Reverse Rotate body & Bend Leg
	case 32:
	case 33:
	case 34:
	case 35:
	case 36:
	case 37:
		modelAngle[BODY].Z -= 7.5;
		modelAngle[LEFTTHIGH].X -= 20;
		modelAngle[LEFTSHANK].X += 28;
		modelAngle[LEFTFOOT].X -= 15;

		modelAngle[RIGHTTHIGH].X -= 20;
		modelAngle[RIGHTSHANK].X += 28;
		modelAngle[RIGHTFOOT].X -= 15;
		break;
		// Reverse Rotate body
	case 38:
	case 39:
	case 40:
	case 41:
	case 42:
	case 43:
		modelAngle[BODY].Z -= 7.5;
		break;
		// Reverse Rotate body & hold Arm
	case 44:
	case 45:
	case 46:
		modelAngle[BODY].Z -= 7.5;
		modelAngle[LEFTUPPERARM].Z += 10;
		modelAngle[RIGHTLOWERARM].Y += 35;

		modelAngle[LEFTHAND].X += 15;
		modelAngle[RIGHTHAND].X += 15;
		break;
	case 47:
	case 48:
	case 49:
		modelAngle[BODY].Z -= 7.5;
		modelAngle[LEFTUPPERARM].Z += 10;
		modelAngle[RIGHTLOWERARM].X += 30;

		modelAngle[LEFTHAND].X += 15;
		modelAngle[RIGHTHAND].X += 15;
		break;
	case 50:
		modelAngle[LEFTUPPERARM].X += 60;
		modelAngle[RIGHTUPPERARM].X -= 15;
		break;
		// Stand up

	case 51:
	case 52:
	case 53:
	case 54:
	case 55:
	case 56:
		modelAngle[LEFTTHIGH].X += 20;
		modelAngle[LEFTSHANK].X -= 28;
		modelAngle[LEFTFOOT].X += 15;

		modelAngle[RIGHTTHIGH].X += 20;
		modelAngle[RIGHTSHANK].X -= 28;
		modelAngle[RIGHTFOOT].X += 15;

		modelAngle[BODY].X -= 5;
		bodyPosition[1] += 0.65;
		break;
	default:
		break;
	}
	return;
}

// Locking-Wrist Twirl
void lockingWT(int frame)
{
	switch (frame)
	{
		// Lift Right hand & Stretch Left leg
	case 0:
	case 1:
	case 2:
		// ARM
		modelAngle[RIGHTUPPERARM].Z -= 22.5;
		modelAngle[RIGHTLOWERARM].Z += 37.5;
		// LEG
		modelAngle[LEFTTHIGH].X -= 15;
		modelAngle[LEFTSHANK].X += 15;
		// HEAD
		modelAngle[HEAD].X += 7.5;
		break;
	case 3:
		// ARM
		modelAngle[RIGHTUPPERARM].Z -= 22.5;
		modelAngle[RIGHTLOWERARM].Z += 37.5;
		// LEG
		modelAngle[LEFTTHIGH].X += 15;
		modelAngle[LEFTSHANK].X -= 15;
		// HEAD
		modelAngle[HEAD].X += 7.5;
		break;
	case 4:
	case 5:
		// HAND
		modelAngle[RIGHTHAND].Y += 40;
		// ARM
		modelAngle[RIGHTUPPERARM].X -= 45;
		// LEG
		modelAngle[LEFTTHIGH].X += 15;
		modelAngle[LEFTSHANK].X -= 15;
		// HEAD
		modelAngle[HEAD].X -= 10;
		break;
	case 6:
		// HAND
		modelAngle[RIGHTHAND].Y += 40;
		// ARM
		modelAngle[RIGHTUPPERARM].X -= 45;
		// HEAD
		modelAngle[HEAD].X -= 10;
		break;
		// Put Right hand & Stretch Right leg
	case 7:
	case 8:
	case 9:
		// HAND
		modelAngle[RIGHTHAND].Y -= 40;
		// ARM
		modelAngle[RIGHTUPPERARM].X += 45;
		// HEAD
		modelAngle[HEAD].X += 7.5;
		// LEG
		modelAngle[RIGHTTHIGH].X -= 15;
		modelAngle[RIGHTSHANK].X += 15;
		break;
	case 10:
		// ARM
		modelAngle[RIGHTUPPERARM].Z += 22.5;
		modelAngle[RIGHTLOWERARM].Z -= 37.5;
		// HEAD
		modelAngle[HEAD].X += 7.5;
		// LEG
		modelAngle[RIGHTTHIGH].X += 15;
		modelAngle[RIGHTSHANK].X -= 15;
		break;
	case 11:
	case 12:
		// ARM
		modelAngle[RIGHTUPPERARM].Z += 22.5;
		modelAngle[RIGHTLOWERARM].Z -= 37.5;
		// HEAD
		modelAngle[HEAD].X -= 10;
		// LEG
		modelAngle[RIGHTTHIGH].X += 15;
		modelAngle[RIGHTSHANK].X -= 15;
		break;
	case 13:
		// ARM
		modelAngle[RIGHTUPPERARM].Z += 22.5;
		modelAngle[RIGHTLOWERARM].Z -= 37.5;
		// HEAD
		modelAngle[HEAD].X -= 10;
		break;
		// Lift Left hand & Stretch Left leg
	case 14:
	case 15:
	case 16:
		// ARM
		modelAngle[LEFTUPPERARM].Z += 22.5;
		modelAngle[LEFTLOWERARM].Z -= 37.5;
		// LEG
		modelAngle[LEFTTHIGH].X -= 15;
		modelAngle[LEFTSHANK].X += 15;
		// HEAD
		modelAngle[HEAD].X += 7.5;
		break;
	case 17:
		// ARM
		modelAngle[LEFTUPPERARM].Z += 22.5;
		modelAngle[LEFTLOWERARM].Z -= 37.5;
		// LEG
		modelAngle[LEFTTHIGH].X += 15;
		modelAngle[LEFTSHANK].X -= 15;
		// HEAD
		modelAngle[HEAD].X += 7.5;
		break;
	case 18:
	case 19:
		// HAND
		modelAngle[LEFTHAND].Y -= 40;
		// ARM
		modelAngle[LEFTUPPERARM].X -= 45;
		// LEG
		modelAngle[LEFTTHIGH].X += 15;
		modelAngle[LEFTSHANK].X -= 15;
		// HEAD
		modelAngle[HEAD].X -= 10;
		break;
	case 20:
		// HAND
		modelAngle[LEFTHAND].Y -= 40;
		// ARM
		modelAngle[LEFTUPPERARM].X -= 45;
		// HEAD
		modelAngle[HEAD].X -= 10;
		break;
		// Put Left hand & Stretch Right leg
	case 21:
	case 22:
	case 23:
		// HAND
		modelAngle[LEFTHAND].Y += 40;
		// ARM
		modelAngle[LEFTUPPERARM].X += 45;
		// HEAD
		modelAngle[HEAD].X += 7.5;
		// LEG
		modelAngle[RIGHTTHIGH].X -= 15;
		modelAngle[RIGHTSHANK].X += 15;
		break;
	case 24:
		// ARM
		modelAngle[LEFTUPPERARM].Z -= 22.5;
		modelAngle[LEFTLOWERARM].Z += 37.5;
		// HEAD
		modelAngle[HEAD].X += 7.5;
		// LEG
		modelAngle[RIGHTTHIGH].X += 15;
		modelAngle[RIGHTSHANK].X -= 15;
		break;
	case 25:
	case 26:
		// ARM
		modelAngle[LEFTUPPERARM].Z -= 22.5;
		modelAngle[LEFTLOWERARM].Z += 37.5;
		// HEAD
		modelAngle[HEAD].X -= 10;
		// LEG
		modelAngle[RIGHTTHIGH].X += 15;
		modelAngle[RIGHTSHANK].X -= 15;
		break;
	case 27:
		// ARM
		modelAngle[LEFTUPPERARM].Z -= 22.5;
		modelAngle[LEFTLOWERARM].Z += 37.5;
		// HEAD
		modelAngle[HEAD].X -= 10;
		break;
		// Both hands & Stretch Left leg
	case 28:
	case 29:
	case 30:
		// ARM
		modelAngle[RIGHTUPPERARM].Z -= 22.5;
		modelAngle[RIGHTLOWERARM].Z += 37.5;
		modelAngle[LEFTUPPERARM].Z += 22.5;
		modelAngle[LEFTLOWERARM].Z -= 37.5;

		// LEG
		modelAngle[LEFTTHIGH].X -= 15;
		modelAngle[LEFTSHANK].X += 15;
		// HEAD
		modelAngle[HEAD].X += 7.5;
		break;
	case 31:
		// ARM
		modelAngle[RIGHTUPPERARM].Z -= 22.5;
		modelAngle[RIGHTLOWERARM].Z += 37.5;
		modelAngle[LEFTUPPERARM].Z += 22.5;
		modelAngle[LEFTLOWERARM].Z -= 37.5;
		// LEG
		modelAngle[LEFTTHIGH].X += 15;
		modelAngle[LEFTSHANK].X -= 15;
		// HEAD
		modelAngle[HEAD].X += 7.5;
		break;
	case 32:
	case 33:
		// HAND
		modelAngle[RIGHTHAND].Y += 40;
		modelAngle[LEFTHAND].Y -= 40;
		// ARM
		modelAngle[RIGHTUPPERARM].X -= 45;
		modelAngle[LEFTUPPERARM].X -= 45;
		// LEG
		modelAngle[LEFTTHIGH].X += 15;
		modelAngle[LEFTSHANK].X -= 15;
		// HEAD
		modelAngle[HEAD].X -= 10;
		break;
	case 34:
		// HAND
		modelAngle[RIGHTHAND].Y += 40;
		modelAngle[LEFTHAND].Y -= 40;
		// ARM
		modelAngle[RIGHTUPPERARM].X -= 45;
		modelAngle[LEFTUPPERARM].X -= 45;
		// HEAD
		modelAngle[HEAD].X -= 10;
		break;
		// Both hands & Stretch Right leg
	case 35:
	case 36:
	case 37:
		// HAND
		modelAngle[RIGHTHAND].Y -= 40;
		modelAngle[LEFTHAND].Y += 40;
		// ARM
		modelAngle[RIGHTUPPERARM].X += 45;
		modelAngle[LEFTUPPERARM].X += 45;
		// HEAD
		modelAngle[HEAD].X += 7.5;
		// LEG
		modelAngle[RIGHTTHIGH].X -= 15;
		modelAngle[RIGHTSHANK].X += 15;
		break;
	case 38:
		// ARM
		modelAngle[RIGHTUPPERARM].Z += 22.5;
		modelAngle[LEFTUPPERARM].Z -= 22.5;
		modelAngle[RIGHTLOWERARM].Z -= 37.5;
		modelAngle[LEFTLOWERARM].Z += 37.5;
		// HEAD
		modelAngle[HEAD].X += 7.5;
		// LEG
		modelAngle[RIGHTTHIGH].X += 15;
		modelAngle[RIGHTSHANK].X -= 15;
		break;
	case 39:
	case 40:
		// ARM
		modelAngle[RIGHTUPPERARM].Z += 22.5;
		modelAngle[LEFTUPPERARM].Z -= 22.5;
		modelAngle[RIGHTLOWERARM].Z -= 37.5;
		modelAngle[LEFTLOWERARM].Z += 37.5;
		// HEAD
		modelAngle[HEAD].X -= 10;
		// LEG
		modelAngle[RIGHTTHIGH].X += 15;
		modelAngle[RIGHTSHANK].X -= 15;
		break;
	case 41:
		// ARM
		modelAngle[RIGHTUPPERARM].Z += 22.5;
		modelAngle[LEFTUPPERARM].Z -= 22.5;
		modelAngle[RIGHTLOWERARM].Z -= 37.5;
		modelAngle[LEFTLOWERARM].Z += 37.5;
		// HEAD
		modelAngle[HEAD].X -= 10;
		break;
	}
}

//Locking-Scooba Hop
void lockingSH(int frame)
{
	switch (frame)
	{
		// Lift Left leg
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
		// LEG
		modelAngle[LEFTTHIGH].X -= 7.5;
		modelAngle[LEFTSHANK].X += 7.5;
		// ARM
		modelAngle[LEFTUPPERARM].Z += 15;
		modelAngle[RIGHTUPPERARM].Z -= 15;
		modelAngle[LEFTLOWERARM].Z -= 26;
		modelAngle[RIGHTLOWERARM].Z += 26;
		break;
		// Kick Left leg
	case 6:
		// LEG
		modelAngle[LEFTTHIGH].X += 15;
		modelAngle[LEFTSHANK].X -= 15;
		// ARM
		modelAngle[LEFTLOWERARM].Z += 26;
		modelAngle[RIGHTLOWERARM].Z -= 26;
		break;
	case 7:
		// LEG
		modelAngle[LEFTTHIGH].Z += 15;
		// ARM
		modelAngle[LEFTLOWERARM].Z += 26;
		modelAngle[RIGHTLOWERARM].Z -= 26;
		break;
	case 8:
		// LEG
		modelAngle[LEFTTHIGH].X += 15;
		modelAngle[LEFTSHANK].X -= 15;
		// ARM
		modelAngle[LEFTLOWERARM].Z += 26;
		modelAngle[RIGHTLOWERARM].Z -= 26;
		break;
	case 9:
		// LEG
		modelAngle[LEFTTHIGH].Z += 15;
		// ARM
		modelAngle[LEFTLOWERARM].Z += 26;
		modelAngle[RIGHTLOWERARM].Z -= 26;
		break;
	case 10:
		// LEG
		modelAngle[LEFTTHIGH].X += 15;
		modelAngle[LEFTSHANK].X -= 15;
		// ARM
		modelAngle[LEFTLOWERARM].Z += 26;
		modelAngle[RIGHTLOWERARM].Z -= 26;
		break;
	case 11:
		// LEG
		modelAngle[LEFTTHIGH].Z += 15;
		// ARM
		modelAngle[LEFTLOWERARM].Z += 26;
		modelAngle[RIGHTLOWERARM].Z -= 26;
		break;
		// Put Left leg
	case 12:
	case 13:
	case 14:
	case 15:
	case 16:
	case 17:
		// LEG
		modelAngle[LEFTTHIGH].Z -= 7.5;
		break;
		// Lift Right leg
	case 18:
		// ARM
		modelAngle[LEFTLOWERARM].Z -= 26;
		modelAngle[RIGHTLOWERARM].Z += 26;
		// LEG
		modelAngle[RIGHTTHIGH].X -= 20;
		modelAngle[RIGHTSHANK].X += 40;
		bodyPosition[1] += 0.25;
		break;
	case 19:
		// ARM
		modelAngle[LEFTLOWERARM].Z -= 26;
		modelAngle[RIGHTLOWERARM].Z += 26;
		// LEG
		modelAngle[RIGHTTHIGH].Z -= 10;
		bodyPosition[1] += 0.25;
		break;
	case 20:
		// ARM
		modelAngle[LEFTLOWERARM].Z -= 26;
		modelAngle[RIGHTLOWERARM].Z += 26;
		// LEG
		modelAngle[RIGHTTHIGH].X -= 20;
		modelAngle[RIGHTSHANK].X += 40;
		bodyPosition[1] += 0.25;
		break;
	case 21:
		// ARM
		modelAngle[LEFTLOWERARM].Z -= 26;
		modelAngle[RIGHTLOWERARM].Z += 26;
		// LEG
		modelAngle[RIGHTTHIGH].Z -= 10;
		bodyPosition[1] -= 0.25;
		break;
	case 22:
		// ARM
		modelAngle[LEFTLOWERARM].Z -= 26;
		modelAngle[RIGHTLOWERARM].Z += 26;
		// LEG
		modelAngle[RIGHTTHIGH].X -= 20;
		modelAngle[RIGHTSHANK].X += 40;
		bodyPosition[1] -= 0.25;
		break;
	case 23:
		// ARM
		modelAngle[LEFTLOWERARM].Z -= 26;
		modelAngle[RIGHTLOWERARM].Z += 26;
		// LEG
		modelAngle[RIGHTTHIGH].Z -= 10;
		bodyPosition[1] -= 0.25;
		break;
		// Kick Right leg
	case 24:
	case 25:
	case 26:
		// ARM
		modelAngle[LEFTLOWERARM].Z += 13;
		modelAngle[RIGHTLOWERARM].Z -= 13;
		modelAngle[LEFTUPPERARM].Z -= 7.5;
		modelAngle[RIGHTUPPERARM].Z += 7.5;
		// LEG
		modelAngle[RIGHTTHIGH].Z += 10;
		break;
	case 27:
	case 28:
	case 29:
		// ARM
		modelAngle[LEFTLOWERARM].Z += 13;
		modelAngle[RIGHTLOWERARM].Z -= 13;
		modelAngle[LEFTUPPERARM].Z -= 7.5;
		modelAngle[RIGHTUPPERARM].Z += 7.5;
		// LEG
		modelAngle[RIGHTTHIGH].X += 20;
		modelAngle[RIGHTSHANK].X -= 40;
		break;
		// Kick Right leg
	case 30:
	case 31:
	case 32:
		// ARM
		modelAngle[LEFTLOWERARM].Z += 13;
		modelAngle[RIGHTLOWERARM].Z -= 13;
		modelAngle[LEFTUPPERARM].Z -= 7.5;
		modelAngle[RIGHTUPPERARM].Z += 7.5;
		// LEG
		modelAngle[LEFTTHIGH].X -= 20;
		modelAngle[LEFTSHANK].X += 40;
		bodyPosition[1] += 0.1;
		break;
	case 33:
	case 34:
	case 35:
		// ARM
		modelAngle[LEFTLOWERARM].Z += 13;
		modelAngle[RIGHTLOWERARM].Z -= 13;
		modelAngle[LEFTUPPERARM].Z -= 7.5;
		modelAngle[RIGHTUPPERARM].Z += 7.5;
		// LEG
		modelAngle[LEFTTHIGH].X += 20;
		modelAngle[LEFTSHANK].X -= 40;
		bodyPosition[1] -= 0.1;
		break;
	}
}



// Menu Part
// Menu Function
void menuEvents(int option)
{
	std::vector<CubemapTexture> textures(6);
	textures[0].type = GL_TEXTURE_CUBE_MAP_POSITIVE_X;
	textures[0].fileName = cubeFilesName[0]->right;
	textures[1].type = GL_TEXTURE_CUBE_MAP_NEGATIVE_X;
	textures[1].fileName = cubeFilesName[0]->left;
	textures[2].type = GL_TEXTURE_CUBE_MAP_POSITIVE_Y;
	textures[2].fileName = cubeFilesName[0]->down;
	textures[3].type = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y;
	textures[3].fileName = cubeFilesName[0]->top;
	textures[4].type = GL_TEXTURE_CUBE_MAP_POSITIVE_Z;
	textures[4].fileName = cubeFilesName[0]->front;
	textures[5].type = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z;
	textures[5].fileName = cubeFilesName[0]->back;
	cubemapShader.Init(textures, option);
}

void ModeMenuEvents(int option)
{
	switch (option) {
	case 0:
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case 1:
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	}
}

void SceneMenuEvents(int option)
{
	//std::cout << option << endl;
	sceneNo = option;
	frameCounter = 0;

	std::vector<CubemapTexture> textures(6);
	if (sceneNo <= 1) {
		textures[0].type = GL_TEXTURE_CUBE_MAP_POSITIVE_X;
		textures[0].fileName = cubeFilesName[sceneNo]->right;
		textures[1].type = GL_TEXTURE_CUBE_MAP_NEGATIVE_X;
		textures[1].fileName = cubeFilesName[sceneNo]->left;
		textures[2].type = GL_TEXTURE_CUBE_MAP_POSITIVE_Y;
		textures[2].fileName = cubeFilesName[sceneNo]->down;
		textures[3].type = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y;
		textures[3].fileName = cubeFilesName[sceneNo]->top;
		textures[4].type = GL_TEXTURE_CUBE_MAP_POSITIVE_Z;
		textures[4].fileName = cubeFilesName[sceneNo]->front;
		textures[5].type = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z;
		textures[5].fileName = cubeFilesName[sceneNo]->back;
	}

	cubemapShader.Init(textures, option);
}

void ActionMenuEvents(int option) {
	resetObj(0);

	switch (option)
	{
	case 0:
		action = ATTENTION;
		break;
	case 1:
		action = ATEASE;
		break;
	case 2:
		action = SALUTE;
		break;
	case 3:
		action = WALK;
		break;
	case 4:
		action = RUN;
		break;
	case 5:
		action = SQUATS;
		break;
	case 6:
		action = JUMP;
		break;
	case 7:
		action = PETANQUE;
		break;
	case 8:
		action = LOSE;
		break;
	case 9:
		action = BREAKINGKS;
		break;
	case 10:
		action = BREAKINGICE;
		break;
	case 11:
		action = LOCKINGTWIRL;
		break;
	case 12:
		action = LOCHINGSCOOBA;
		break;
	}

	return;
}

void ShaderMenuEvents(int option)
{
	shaderNo = option;

	program = LoadShaders(shaderList[option]);
	glUseProgram(program);

	MatricesIdx = glGetUniformBlockIndex(program, "MatVP");
	ModelID = glGetUniformLocation(program, "Model");
	M_KaID = glGetUniformLocation(program, "Material.Ka");
	M_KdID = glGetUniformLocation(program, "Material.Kd");
	M_KsID = glGetUniformLocation(program, "Material.Ks");

	if (option == 4)
		partLocation = glGetUniformLocation(program, "partNum");

	return;
}