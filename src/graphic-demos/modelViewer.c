#include "utils/math.h"
#include <time.h>
#include "utils/keys.h"
#include "utils/utils.h"

#define __PRINTF_H_IMPLEMENTATION__
#include "utils/printf.h"

#define __STACK_ALLOC_IMPLEMENTATION__
#include "utils/stack_allocator.h"

int main_(void);
void printHelp(void);

// #define FILLER_SIZE 1024000000
// unsigned char filler[FILLER_SIZE] = {0};

int main(void)
{
	// filler[FILLER_SIZE - 1] = 'A';
	return main_();
}
int main_(void)
{
	unsigned char key = 0;
	printHelp();
	printf("\nPress SPACE to continue.\n");

	while (key != ASCII_SPACE)
	{
		key = b_input();
	}
}

// #define S3L_FLAT 0
// #define S3L_NEAR_CROSS_STRATEGY 0
// #define S3L_PERSPECTIVE_CORRECTION 2
// #define S3L_SORT 0
// #define S3L_STENCIL_BUFFER 0
// #define S3L_Z_BUFFER 1

// void putpixel(int x, int y, char red, char green, char blue);
// void clearScreen();
// void sampleTexture(const uint8_t *tex, int32_t u, int32_t v, uint8_t *r, uint8_t *g, uint8_t *b);

// unsigned char *frame_buffer;
// unsigned char *video_memory;
// uint16_t x_res, y_res;
// uint8_t depth;
// uint64_t frameBufferSize;

#define S3L_RESOLUTION_X 800
#define S3L_RESOLUTION_Y 600

#define S3L_PIXEL_FUNCTION drawPixel

#include "utils/small3dlib.h"

#define TEXTURE_W 128
#define TEXTURE_H 128



#include "models/houseTexture.h"
#include "models/houseModel.h"

#include "models/chestTexture.h"
#include "models/chestModel.h"

#include "models/plantTexture.h"
#include "models/plantModel.h"

#include "models/cat1Model.h"
#include "models/cat2Model.h"
#include "models/catTexture.h"

#define MODE_TEXTUERED 0
#define MODE_SINGLE_COLOR 1
#define MODE_NORMAL_SMOOTH 2
#define MODE_NORMAL_SHARP 3
#define MODE_BARYCENTRIC 4
#define MODE_TRIANGLE_INDEX 5

void printHelp(void)
{
	printf("Modelviewer: example program for small3dlib.\n\n");

	printf("contols:\n");
	printf("  arrows           rotate\n");
	printf("  ctrl + U/D       go closer/further\n");
	printf("  ctrl + L/R       zoom (FOV) closer/further\n");
	printf("  space            next model\n");
	printf("  0 - 5            set display mode\n");
	printf("  w                toggle wireframe\n");
	printf("  l                toggle light\n");
	printf("  f                toggle fog\n");
	printf("  b                change backface culling\n");
	printf("  n                toggle noise\n");
	printf("Ported from the original example by Miloslav Ciz, released under CC0 1.0\n");
}

// S3L_Unit houseNormals[HOUSE_VERTEX_COUNT * 3];
// S3L_Unit chestNormals[CHEST_VERTEX_COUNT * 3];
// S3L_Unit catNormals[CAT1_VERTEX_COUNT * 3];
// S3L_Unit plantNormals[PLANT_VERTEX_COUNT * 3];

// S3L_Unit catVertices[CAT1_VERTEX_COUNT * 3];
// const S3L_Index *catTriangleIndices = cat1TriangleIndices;
// const S3L_Unit *catUVs = cat1UVs;
// const S3L_Index *catUVIndices = cat1UVIndices;

// S3L_Model3D catModel;

// S3L_Model3D model;
// const uint8_t *texture;
// const S3L_Unit *uvs;
// const S3L_Unit *normals;
// const S3L_Index *uvIndices;

// S3L_Scene scene;

// uint32_t frame = 0;

// void setPixel(int x, int y, char red, char green, char blue)
// {
// 	int offset = ((y * x_res) + x) * (depth / 8);
// 	frame_buffer[offset + 0] = blue;
// 	frame_buffer[offset + 1] = green;
// 	frame_buffer[offset + 2] = red;
// }

// void animate(double time)
// {
// 	time = (1.0 + sin(time * 8)) / 2;

// 	S3L_Unit t = time * S3L_F;

// 	for (S3L_Index i = 0; i < CAT1_VERTEX_COUNT * 3; i += 3)
// 	{
// 		S3L_Unit v0[3], v1[3];

// 		v0[0] = cat1Vertices[i];
// 		v0[1] = cat1Vertices[i + 1];
// 		v0[2] = cat1Vertices[i + 2];

// 		v1[0] = cat2Vertices[i];
// 		v1[1] = cat2Vertices[i + 1];
// 		v1[2] = cat2Vertices[i + 2];

// 		catVertices[i] = S3L_interpolateByUnit(v0[0], v1[0], t);
// 		catVertices[i + 1] = S3L_interpolateByUnit(v0[1], v1[1], t);
// 		catVertices[i + 2] = S3L_interpolateByUnit(v0[2], v1[2], t);
// 	}
// }

// uint32_t previousTriangle = -1;
// S3L_Vec4 uv0, uv1, uv2;
// uint16_t l0, l1, l2;
// S3L_Vec4 toLight;
// int8_t light = 1;
// int8_t fog = 0;
// int8_t noise = 0;
// int8_t wire = 0;
// int8_t transparency = 0;
// int8_t mode = 0;
// S3L_Vec4 n0, n1, n2, nt;

void drawPixel(S3L_PixelInfo *p)
{
// 	if (p->triangleID != previousTriangle)
// 	{
// 		if (mode == MODE_TEXTUERED)
// 		{
// 			S3L_getIndexedTriangleValues(p->triangleIndex, uvIndices, uvs, 2, &uv0, &uv1, &uv2);
// 		}
// 		else if (mode == MODE_NORMAL_SHARP)
// 		{
// 			S3L_Vec4 v0, v1, v2;
// 			S3L_getIndexedTriangleValues(p->triangleIndex, model.triangles, model.vertices, 3, &v0, &v1, &v2);

// 			S3L_triangleNormal(v0, v1, v2, &nt);

// 			nt.x = S3L_clamp(128 + nt.x / 4, 0, 255);
// 			nt.y = S3L_clamp(128 + nt.y / 4, 0, 255);
// 			nt.z = S3L_clamp(128 + nt.z / 4, 0, 255);
// 		}

// 		if (light || mode == MODE_NORMAL_SMOOTH)
// 		{
// 			S3L_getIndexedTriangleValues(p->triangleIndex, model.triangles, normals, 3, &n0, &n1, &n2);

// 			l0 = 256 + S3L_clamp(S3L_vec3Dot(n0, toLight), -511, 511) / 2;
// 			l1 = 256 + S3L_clamp(S3L_vec3Dot(n1, toLight), -511, 511) / 2;
// 			l2 = 256 + S3L_clamp(S3L_vec3Dot(n2, toLight), -511, 511) / 2;
// 		}

// 		previousTriangle = p->triangleID;
// 	}

// 	if (wire)
// 		if (p->barycentric[0] != 0 &&
// 			p->barycentric[1] != 0 &&
// 			p->barycentric[2] != 0)
// 			return;

// 	uint8_t
// 		r = 0,
// 		g = 0,
// 		b = 0;

// 	int8_t transparent = 0;

// 	switch (mode)
// 	{
// 	case MODE_TEXTUERED:
// 	{
// 		S3L_Unit uv[2];

// 		uv[0] = S3L_interpolateBarycentric(uv0.x, uv1.x, uv2.x, p->barycentric);
// 		uv[1] = S3L_interpolateBarycentric(uv0.y, uv1.y, uv2.y, p->barycentric);

// 		sampleTexture(texture, uv[0] / 4, uv[1] / 4, &r, &g, &b);

// 		if (transparency && r == 255 && g == 0 && b == 0)
// 			transparent = 1;

// 		break;
// 	}

// 	case MODE_SINGLE_COLOR:
// 	{
// 		r = 128;
// 		g = 128;
// 		b = 128;

// 		break;
// 	}

// 	case MODE_NORMAL_SMOOTH:
// 	{
// 		S3L_Vec4 n;

// 		n.x = S3L_interpolateBarycentric(n0.x, n1.x, n2.x, p->barycentric);
// 		n.y = S3L_interpolateBarycentric(n0.y, n1.y, n2.y, p->barycentric);
// 		n.z = S3L_interpolateBarycentric(n0.z, n1.z, n2.z, p->barycentric);

// 		S3L_vec3Normalize(&n);

// 		r = S3L_clamp(128 + n.x / 4, 0, 255);
// 		g = S3L_clamp(128 + n.y / 4, 0, 255);
// 		b = S3L_clamp(128 + n.z / 4, 0, 255);

// 		break;
// 	}

// 	case MODE_NORMAL_SHARP:
// 	{
// 		r = nt.x;
// 		g = nt.y;
// 		b = nt.z;
// 		break;
// 	}

// 	case MODE_BARYCENTRIC:
// 	{
// 		r = p->barycentric[0] >> 1;
// 		g = p->barycentric[1] >> 1;
// 		b = p->barycentric[2] >> 1;
// 		break;
// 	}

// 	case MODE_TRIANGLE_INDEX:
// 	{
// 		r = S3L_min(p->triangleIndex, 255);
// 		g = r;
// 		b = r;
// 	}

// 	default:
// 		break;
// 	}

// 	if (light)
// 	{
// 		int16_t l = S3L_interpolateBarycentric(l0, l1, l2, p->barycentric);

// 		r = S3L_clamp((((int16_t)r) * l) / S3L_F, 0, 255);
// 		g = S3L_clamp((((int16_t)g) * l) / S3L_F, 0, 255);
// 		b = S3L_clamp((((int16_t)b) * l) / S3L_F, 0, 255);
// 	}

// 	if (fog)
// 	{
// 		int16_t f = ((p->depth - S3L_NEAR) * 255) / (S3L_F * 64);

// 		f *= 2;

// 		r = S3L_clamp(((int16_t)r) + f, 0, 255);
// 		g = S3L_clamp(((int16_t)g) + f, 0, 255);
// 		b = S3L_clamp(((int16_t)b) + f, 0, 255);
// 	}

// 	if (transparency && transparent)
// 	{
// 		S3L_zBufferWrite(p->x, p->y, p->previousZ);
// 		return;
// 	}

// 	if (noise)
// 		setPixel(p->x + rand() % 8, p->y + rand() % 8, r, g, b);
// 	else
// 		setPixel(p->x, p->y, r, g, b);
}

// void switchBuffers()
// {
// 	memcpy(video_memory, frame_buffer, frameBufferSize);
// }

// void draw(void)
// {
// 	S3L_newFrame();
// 	clearScreen();
// 	S3L_drawScene(scene);
// }

// void setModel(uint8_t index)
// {
// 	printf("\nSetting model nmber %d.\n", index);

// #define modelCase(n, m)                                          \
// 	case n:                                                      \
// 	{                                                            \
// 		texture = m##Texture;                                    \
// 		uvs = m##UVs;                                            \
// 		uvIndices = m##UVIndices;                                \
// 		normals = m##Normals;                                    \
// 		scene.models[0] = m##Model;                              \
// 		S3L_computeModelNormals(scene.models[0], m##Normals, 0); \
// 		break;                                                   \
// 	}

// 	switch (index)
// 	{
// 		modelCase(0, house)
// 			modelCase(1, chest)
// 				modelCase(2, cat)
// 					modelCase(3, plant)

// 						default : break;
// 	}

// #undef modelCase

// 	S3L_transform3DInit(&(scene.models[0].transform));
// 	S3L_drawConfigInit(&(scene.models[0].config));

// 	if (index == 3)
// 	{
// 		scene.models[0].config.backfaceCulling = 0;
// 		transparency = 1;
// 	}
// 	else
// 	{
// 		scene.models[0].config.backfaceCulling = 2;
// 		transparency = 0;
// 	}

// 	printf("vertices: %d\n", scene.models[0].vertexCount);
// 	printf("triangles: %d\n", scene.models[0].triangleCount);
// }

// int16_t fps = 0;
// static StackAllocator *stackAllocator;

int main__(void)
{
	unsigned char key = 0;
	printHelp();
	printf("\nPress SPACE to continue.\n");

	while (key != ASCII_SPACE)
	{
		key = b_input();
	}

	// stackAllocator = stackAllocatorCreateP(((uint64_t *)(0xFFFF800000F00000)));
	// // Gather video memory address, x & y resolution, and BPP
	// video_memory = (unsigned char *)(*(uint64_t *)(0x5080));
	// x_res = *(uint16_t *)(0x5088);
	// y_res = *(uint16_t *)(0x508A);
	// depth = 32;
	// frameBufferSize = x_res * y_res * 4;
	// frame_buffer = stackAllocatorAlloc(stackAllocator, frameBufferSize);

	// toLight.x = 10;
	// toLight.y = 10;
	// toLight.z = 10;

	// S3L_vec3Normalize(&toLight);

	// S3L_sceneInit(&model, 1, &scene);

	// houseModelInit();
	// chestModelInit();
	// plantModelInit();
	// cat1ModelInit();
	// cat2ModelInit();

	// scene.camera.transform.translation.z = -S3L_F * 8;

	// catModel = cat1Model;
	// catModel.vertices = catVertices;
	// animate(0);

	// int8_t modelIndex = 0;
	// int8_t modelsTotal = 4;
	// setModel(0);

	// int running = 1;

	// while (running)
	// {
	// 	draw();
	// 	switchBuffers();

	// 	unsigned char key = 0;

	// 	int16_t rotationStep = 3000;
	// 	int16_t moveStep = 3000;
	// 	int16_t fovStep = 3000;

	// 	switch (key)
	// 	{
	// 	case ASCII_q:
	// 		running = 0;
	// 		break;
	// 	case ASCII_l:
	// 		light = !light;
	// 		break;
	// 	case ASCII_f:
	// 		fog = !fog;
	// 		break;
	// 	case ASCII_n:
	// 		noise = !noise;
	// 		break;
	// 	case ASCII_t:
	// 		wire = !wire;
	// 		break;
	// 	case ASCII_w:
	// 		model.transform.rotation.x -= rotationStep;
	// 		break;
	// 	case ASCII_a:
	// 		model.transform.rotation.y += rotationStep;
	// 		break;
	// 	case ASCII_s:
	// 		model.transform.rotation.x += rotationStep;
	// 		break;
	// 	case ASCII_d:
	// 		model.transform.rotation.y -= rotationStep;
	// 		break;

	// 	case ASCII_W:
	// 		model.transform.rotation.x -= rotationStep;
	// 		break;
	// 	case ASCII_A:
	// 		model.transform.rotation.y += rotationStep;
	// 		break;
	// 	case ASCII_S:
	// 		model.transform.rotation.x += rotationStep;
	// 		break;
	// 	case ASCII_D:
	// 		model.transform.rotation.y -= rotationStep;
	// 		break;

	// 	case ASCII_SPACE:
	// 		modelIndex = (modelIndex + 1) % modelsTotal;
	// 		setModel(modelIndex);
	// 		break;

	// 	case ASCII_o:
	// 		scene.camera.focalLength = S3L_min(S3L_F * 5, scene.camera.focalLength + fovStep);
	// 		break;
	// 	case ASCII_p:
	// 		scene.camera.focalLength = S3L_max(S3L_F / 2, scene.camera.focalLength - fovStep);
	// 		break;
	// 	case ASCII_i:
	// 		scene.camera.transform.translation.z = S3L_min(S3L_F, scene.camera.transform.translation.z + moveStep);
	// 		break;
	// 	case ASCII_k:
	// 		scene.camera.transform.translation.z = S3L_max(-S3L_F * 16, scene.camera.transform.translation.z - moveStep);
	// 		break;

	// 	case ASCII_1:
	// 		mode = MODE_TEXTUERED;
	// 		break;
	// 	case ASCII_2:
	// 		mode = MODE_SINGLE_COLOR;
	// 		break;
	// 	case ASCII_3:
	// 		mode = MODE_NORMAL_SMOOTH;
	// 		break;
	// 	case ASCII_4:
	// 		mode = MODE_NORMAL_SHARP;
	// 		break;
	// 	case ASCII_5:
	// 		mode = MODE_BARYCENTRIC;
	// 		break;
	// 	case ASCII_6:
	// 		mode = MODE_TRIANGLE_INDEX;
	// 		break;
	// 	}
	// 	frame++;
	// }

	return 0;
}

// void putpixel(int x, int y, char red, char green, char blue)
// {
// 	int offset = ((y * x_res) + x) * (depth / 8);
// 	frame_buffer[offset + 0] = blue;
// 	frame_buffer[offset + 1] = green;
// 	frame_buffer[offset + 2] = red;
// }

// void clearScreen()
// {
//     memset(frame_buffer, 0, frameBufferSize);
// }

// void sampleTexture(const uint8_t *tex, int32_t u, int32_t v, uint8_t *r, uint8_t *g, uint8_t *b)
// {
//   u = S3L_wrap(u,TEXTURE_W);
//   v = S3L_wrap(v,TEXTURE_H);

//   const uint8_t *t = tex + (v * TEXTURE_W + u) * 4;

//   *r = *t;
//   t++;
//   *g = *t;
//   t++;
//   *b = *t;
// }
