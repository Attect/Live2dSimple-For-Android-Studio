package jp.live2d.sample;

public final class JniBridge {

	private static final String LIBRARY_NAME = "Live2DSimple";

	static {
		System.loadLibrary(LIBRARY_NAME);
	}

	public static native void nativeOnSurfaceCreated();
	public static native void nativeOnSurfaceChanged(int width, int height);
	public static native void nativeOnDrawFrame();
	
	public static native void nativeLoadTexture(int no,int[] pixels, int width, int height);
	public static native void nativeLoadLive2DModel(byte[] bytes, int len);
}
