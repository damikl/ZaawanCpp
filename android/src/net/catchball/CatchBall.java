package net.catchball;

import java.io.IOException;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.app.Activity;
import android.content.Context;
import android.content.pm.ActivityInfo;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.content.res.AssetFileDescriptor;
import android.content.res.AssetManager;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;
import android.view.MotionEvent;

public class CatchBall extends Activity {
	private GLSurfaceView mGLView;

	static {
		System.loadLibrary("catchball");
	}

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		mGLView = new CatchBallGLSurface(this);
		setContentView(mGLView);
		
    //Force landscape
    setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
	}
    
	@Override
	protected void onPause() {
		super.onPause();
		mGLView.onPause();
	}

	@Override
	protected void onResume() {
		super.onResume();
		mGLView.onResume();
	}
	
}

class CatchBallGLSurface extends GLSurfaceView {
	CatchBallRenderer mRenderer;
	private static final String TAG = "javaCatchBallGLSurface";
	private static native void nativePause();
	private static native void processTouch(float start_x, float start_y, float end_x, float end_y); 
	
	public CatchBallGLSurface(Context context) {
		super(context);
		mRenderer = new CatchBallRenderer(context);
		setRenderer(mRenderer);
	}

	public boolean onTouchEvent(final MotionEvent ev) {
		if (ev.getAction() == MotionEvent.ACTION_DOWN) {
			nativePause();
			
		}
		final int historySize = ev.getHistorySize();
	    final int pointerCount = ev.getPointerCount();
	/*    for (int h = 0; h < historySize; h++) {
	        System.out.printf("At time %d:", ev.getHistoricalEventTime(h));
	        for (int p = 0; p < pointerCount; p++) {
	            System.out.printf("  pointer %d: (%f,%f)",
	                ev.getPointerId(p), ev.getHistoricalX(p, h), ev.getHistoricalY(p, h));
	        }
	    }*/
	    System.out.printf("At time %d:", ev.getEventTime());
	    if(historySize > 0)
	    for (int p = 0; p < pointerCount; p++) {
	    	Log.v(TAG, "Aktualny punkt:" + ev.getX(p) + "  "+ ev.getY(p));
	    //    System.out.printf("  pointer %d: (%f,%f)",ev.getPointerId(p), ev.getX(p), ev.getY(p));
	    	  int h = historySize - 1;
	    	  processTouch(ev.getHistoricalX(p, h), ev.getHistoricalY(p, h),ev.getX(p),ev.getY(p) );
	    }
		return true;
	}
	public boolean onKeyEvent(final KeyEvent ev)
	{
		
		return true;
	}
}

class CatchBallRenderer implements GLSurfaceView.Renderer {
	private Context context;
	public CatchBallRenderer (Context context) {
		this.context = context;
	}
	
	public void onSurfaceCreated(GL10 gl, EGLConfig config) {
		// return apk file path (or null on error)
		String apkFilePath = null;
		ApplicationInfo appInfo = null;
		PackageManager packMgmr = context.getPackageManager();
		try {
	    appInfo = packMgmr.getApplicationInfo("net.catchball", 0);
    } catch (NameNotFoundException e) {
	    e.printStackTrace();
	    throw new RuntimeException("Unable to locate assets, aborting...");
    }
		apkFilePath = appInfo.sourceDir;
		nativeInit(apkFilePath);
	}

	public void onSurfaceChanged(GL10 gl, int w, int h) {
		// gl.glViewport(0, 0, w, h);
		nativeResize(w, h);
	}

	public void onDrawFrame(GL10 gl) {
		nativeRender();
	}

	private static native void nativeInit(String apkPath);

	private static native void nativeResize(int w, int h);

	private static native void nativeRender();
}
