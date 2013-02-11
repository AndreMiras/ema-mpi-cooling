package com.example.guesswhatgame_bauerdonnadieu;

import android.os.Bundle;
import android.app.Activity;
import android.content.Intent;
import android.view.Menu;
import android.view.View;

public class StartActivity extends Activity 
{
	private final int RESULT_CLOSE_ALL = 30;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_start);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.activity_start, menu);
		return true;
	}
	
	public void goToMapActivityClick(View v)
    {	
		Intent activity = new Intent(this,MyMapActivity.class);
		startActivityForResult(activity, RESULT_CLOSE_ALL);
    }
	
	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data)
	{
		switch ( resultCode)
		{
			case RESULT_CLOSE_ALL:
				setResult(RESULT_CLOSE_ALL);
				StartActivity.this.finish();
		}
		
		super.onActivityResult(requestCode, resultCode, data);
	}

}
