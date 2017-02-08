package jp.live2d.sample;

import java.io.IOException;
import java.io.InputStream;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.content.Context;
import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.opengl.GLSurfaceView.Renderer;

public class SampleGLRenderer implements Renderer {
	private Context context;
	
	private final String MODEL_PATH = "haru/haru.moc" ;
	private final String TEXTURE_PATHS[] =
		{
			"haru/haru.1024/texture_00.png" ,
			"haru/haru.1024/texture_01.png" ,
			"haru/haru.1024/texture_02.png"
		} ;
	
	public void setContext(Context c)
	{
		context=c;
	}

	@Override
	public void onDrawFrame(GL10 gl) {
		JniBridge.nativeOnDrawFrame();
	}

	@Override
	public void onSurfaceChanged(GL10 gl, int width, int height) {
		JniBridge.nativeOnSurfaceChanged(width, height);
	}

	@Override
	public void onSurfaceCreated(GL10 gl, EGLConfig config) {
		JniBridge.nativeOnSurfaceCreated();
		Resources res = context.getResources();  
		try{
			
			InputStream modelData = res.openRawResource(R.raw.haru);  
			
//			InputStream modelData = context.getAssets().open( MODEL_PATH ) ;
			int len=modelData.available();
			byte[] bytes=new byte[len];
			modelData.read(bytes, 0, len);
			JniBridge.nativeLoadLive2DModel(bytes,len);
			modelData.close() ;
		}
		catch(IOException e)
		{
			e.printStackTrace();
		}
		
		// テクスチャで使用するビットマップを読み込んでピクセルデータを取得します。
		try 
		{
			InputStream in = res.openRawResource(R.raw.texture_00);
			final Bitmap bitmap = BitmapFactory.decodeStream( in );
			final int width = bitmap.getWidth();
			final int height = bitmap.getHeight();
			final int[] pixels = new int[width * height];
			bitmap.getPixels(pixels, 0, width, 0, 0, width, height);
			bitmap.recycle();
			
			JniBridge.nativeLoadTexture(0,pixels, width, height);
			in.close();
		} 
		catch (IOException e) 
		{
			e.printStackTrace();
		}
		
		try 
		{
			InputStream in = res.openRawResource(R.raw.texture_01);
			final Bitmap bitmap = BitmapFactory.decodeStream( in );
			final int width = bitmap.getWidth();
			final int height = bitmap.getHeight();
			final int[] pixels = new int[width * height];
			bitmap.getPixels(pixels, 0, width, 0, 0, width, height);
			bitmap.recycle();
			
			JniBridge.nativeLoadTexture(1,pixels, width, height);
			in.close();
		} 
		catch (IOException e) 
		{
			e.printStackTrace();
		}
		
		try 
		{
			InputStream in = res.openRawResource(R.raw.texture_02);
			final Bitmap bitmap = BitmapFactory.decodeStream( in );
			final int width = bitmap.getWidth();
			final int height = bitmap.getHeight();
			final int[] pixels = new int[width * height];
			bitmap.getPixels(pixels, 0, width, 0, 0, width, height);
			bitmap.recycle();
			
			JniBridge.nativeLoadTexture(2,pixels, width, height);
			in.close();
		} 
		catch (IOException e) 
		{
			e.printStackTrace();
		}
			
			
		
	}
}
