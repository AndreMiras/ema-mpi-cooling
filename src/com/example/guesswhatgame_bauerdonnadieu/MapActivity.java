package com.example.guesswhatgame_bauerdonnadieu;

import android.os.Bundle;
import android.app.Activity;
import android.content.Intent;
import android.view.Menu;
import android.view.View;

public class MapActivity extends Activity {
	private final int RESULT_CLOSE_ALL = 30;
	
	private boolean clue1Found = false; 
	private boolean clue2Found = false;
	private boolean clue3Found = false;
	
	//private Intent activity = new Intent(this,SolveActivity.class);
	

	@Override
	protected void onCreate(Bundle savedInstanceState) {		
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_map);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.activity_map, menu);
		return true;
	}
	
	public void goToSolveActivityClick(View v)
    {	
		Intent activity = new Intent(this,SolveActivity.class);
		activity.putExtra("clue1Found", clue1Found);
		activity.putExtra("clue2Found", clue2Found);
		activity.putExtra("clue3Found", clue3Found);
		startActivityForResult(activity, RESULT_CLOSE_ALL);
    }
	
	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data)
	{
		switch ( resultCode)
		{
			case RESULT_CLOSE_ALL:
				setResult(RESULT_CLOSE_ALL);
				MapActivity.this.finish();
		}
		
		super.onActivityResult(requestCode, resultCode, data);
	}
	
	public void fakeClue1(View v)
	{
		clue1Found = true;
	}
	
	public void fakeClue2(View v)
	{
		clue2Found = true;
	}
	
	public void fakeClue3(View v)
	{
		clue3Found = true;
	}
}
