/**
 *
 *  You can modify and use this source freely
 *  only for the development of application related Live2D.
 *
 *  (c) Live2D Inc. All rights reserved.
 */
package jp.live2d.sample;


import android.app.Activity;
import android.os.Bundle;


public class SampleActivity extends Activity
{

    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        
        SampleGLSurfaceView 	view = new SampleGLSurfaceView(this) ;
        setContentView( view ) ;
    }
}
