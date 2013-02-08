package com.example.guesswhatgame_bauerdonnadieu;

import android.os.Bundle;
import android.app.Activity;
import android.content.Intent;
import android.view.Menu;
import android.view.View;

public class SolveActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_solve);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.activity_solve, menu);
		return true;
	}
	
	public void goToMapActivityClick(View v)
    {	
		Intent activity = new Intent(this,MyMapActivity.class);
		startActivity(activity);
    }

}
