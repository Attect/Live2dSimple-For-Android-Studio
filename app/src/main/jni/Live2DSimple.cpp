
#include <jni.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <android/log.h>

#include "Live2D.h"
#include "Live2DModelOpenGL.h"
#include "util/UtSystem.h"

using namespace live2d;
//////////////////////////////////////////////////////////////////////////////

#define LOG_TAG    "jni"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,  LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,  LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

//////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif
JNIEXPORT void JNICALL Java_jp_live2d_sample_JniBridge_nativeLoadTexture(JNIEnv* env, jobject thiz,jint no,jintArray pixels, jint width, jint height);
JNIEXPORT void JNICALL Java_jp_live2d_sample_JniBridge_nativeLoadLive2DModel(JNIEnv* env, jobject thiz,jbyteArray bytes, jint len);

JNIEXPORT void JNICALL Java_jp_live2d_sample_JniBridge_nativeOnSurfaceCreated(JNIEnv* env, jobject thiz);
JNIEXPORT void JNICALL Java_jp_live2d_sample_JniBridge_nativeOnSurfaceChanged(JNIEnv* env, jobject thiz, jint width, jint height);
JNIEXPORT void JNICALL Java_jp_live2d_sample_JniBridge_nativeOnDrawFrame(JNIEnv* env, jobject thiz);

#ifdef __cplusplus
}
#endif

//////////////////////////////////////////////////////////////////////////////

static void printGLString(const char *name, GLenum s) {
	const char *v = (const char *) glGetString(s);
	LOGI("GL %s = %s\n", name, v);
}



//////////////////////////////////////////////////////////////////////////////


static Live2DModelOpenGL* live2DModel;


static float matrix[] = {
	1,0,0,0,
	0,1,0,0,
	0,0,1,0,
	0,0,0,1
};


JNIEXPORT void JNICALL Java_jp_live2d_sample_JniBridge_nativeLoadLive2DModel(JNIEnv* env, jobject thiz, jbyteArray bytes, jint len) {
	LOGI("nativeLoadLive2DModel");

	void* _bytes=  (void*) env->GetPrimitiveArrayCritical(bytes, 0);

	live2DModel=Live2DModelOpenGL::loadModel( _bytes, (int)len);


	live2DModel->setPremultipliedAlpha(false);

	env->ReleasePrimitiveArrayCritical(bytes, _bytes, JNI_ABORT);
}

JNIEXPORT void JNICALL Java_jp_live2d_sample_JniBridge_nativeLoadTexture(JNIEnv* env, jobject thiz,jint no, jintArray pixels, jint width, jint height) {
	LOGI("nativeLoadTexture");

	

	unsigned int*  _pixels = (unsigned int*) env->GetPrimitiveArrayCritical(pixels, 0);

	
	const int size = width * height;
	for (int i = 0; i < size; i++) {
		unsigned int px = _pixels[i];
		_pixels[i] = (
				((px      ) & 0xFF000000) | // A
				((px << 16) & 0x00FF0000) | // R
				((px      ) & 0x0000FF00) | // G
				((px >> 16) & 0x000000FF)	// B
			);
	}
	static GLuint textures[1];

	
	glGenTextures(1, textures);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _pixels);

	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);		
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);		

	LOGI("texture : %d ",no);

	live2DModel->setTexture(no,textures[0]);
	env->ReleasePrimitiveArrayCritical(pixels, _pixels, JNI_ABORT);
}

JNIEXPORT void JNICALL Java_jp_live2d_sample_JniBridge_nativeOnSurfaceCreated(JNIEnv* env, jobject thiz) {
	LOGI("nativeOnSurfaceCreated");

	Live2D::init();

	printGLString("Version",    GL_VERSION);
	printGLString("Vendor",     GL_VENDOR);
	printGLString("Renderer",   GL_RENDERER);
	printGLString("Extensions", GL_EXTENSIONS);

}


JNIEXPORT void JNICALL Java_jp_live2d_sample_JniBridge_nativeOnSurfaceChanged(JNIEnv* env, jobject thiz, jint width, jint height) {
	
	glViewport(0, 0, width, height);

	float w=live2DModel->getCanvasWidth();
	float h=live2DModel->getCanvasHeight();
	LOGI("Live2D Model w: %f  h: %f \n", w, h);

	matrix[0]=1.0/w*2;
	matrix[5]=-1.0/w*2.0*((float)width/height);

	matrix[12]=-1;
	matrix[13]=1;
	live2DModel->setMatrix(matrix);

}


JNIEXPORT void JNICALL Java_jp_live2d_sample_JniBridge_nativeOnDrawFrame(JNIEnv* env, jobject thiz) {
	

	
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	double t = (UtSystem::getUserTimeMSec()/1000.0) * 2 * M_PI ;
	live2DModel->setParamFloat("PARAM_ANGLE_X", (float)(30 * sin( t/3.0 )) );

	live2DModel->update();
	live2DModel->draw();

}
