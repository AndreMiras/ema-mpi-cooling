package com.example.guesswhatgame_bauerdonnadieu;

import android.os.Bundle;
import android.app.Activity;
import android.app.Dialog;
import android.content.Intent;
import android.text.Editable;
import android.view.Menu;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;
import android.app.AlertDialog;
import android.app.AlertDialog.Builder;
import android.content.DialogInterface;
import android.content.res.Resources;

public class SolveActivity extends Activity 
{
	private final int RESULT_CLOSE_ALL = 30;
	
	// Indices des boites de dialogues à afficher
	private static final int DIALOG_WRONG = 10;
	private static final int DIALOG_GOOD  = 20;
	
	private boolean clue1Found = false; 
	private boolean clue2Found = false;
	private boolean clue3Found = false;
	
	// Solution de l'énigme
	private static String enigmaSolution = "toto a la plage";

	@Override
	protected void onCreate(Bundle savedInstanceState) 
	{
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_solve);
		
		Bundle extras = getIntent().getExtras();		
		if(extras != null) 
		{
			this.clue1Found = extras.getBoolean("clue1Found");
			this.clue2Found = extras.getBoolean("clue2Found");
			this.clue3Found = extras.getBoolean("clue3Found");			
		}		
		
		if(this.clue1Found)
		{
			TextView tv = (TextView)findViewById(R.id.textClue1Val);
			int txt_id = R.string.t_clue1_val;
			Resources res = this.getResources();
			String txt = res.getString(txt_id);
			tv.setText(txt);
		}
		if(this.clue2Found)
		{
			((TextView)findViewById(R.id.textClue2Val)).setText(this.getResources().getString(R.string.t_clue2_val));
		}
		if(this.clue3Found)
		{
			((TextView)findViewById(R.id.textClue3Val)).setText(this.getResources().getString(R.string.t_clue3_val));
		}
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) 
	{
		//this adds items to the action bar if it is present.
		//Inflate themenu;
		
		getMenuInflater().inflate(R.menu.activity_solve, menu);
		return true;
	}
	
	public void goToMapActivityClick(View v) 
	{
		SolveActivity.this.finish();
	}

	public void onTryClick(View v) 
	{
		boolean found = false;
		
		// Récupération de la saisie utilisateur
		EditText ev = (EditText)findViewById(R.id.editSolution);
		Editable ed = ev.getText();
		String userResponse = ed.toString();
		
		userResponse   = userResponse  .replaceAll("\\s", "");
		enigmaSolution = enigmaSolution.replaceAll("\\s", "");
		
		// Comparaison avec la solution de l'énigme
		if ( userResponse.equalsIgnoreCase( enigmaSolution ) )
			found = true;		
		
		// Affichage de la dialog correspondante
		if ( found ) showDialog(DIALOG_GOOD );		
		else         showDialog(DIALOG_WRONG);
		
	}

	@Override
	protected Dialog onCreateDialog(int id) 
	{
		switch (id) 
		{
			case DIALOG_GOOD:
			{
				// CreateoutAlterDialog
				Builder builder = new AlertDialog.Builder(this);
				builder.setMessage("Congratulation");
				builder.setCancelable(true);
				builder.setPositiveButton("Exit", new OkOnClickListener());
				//builder.setNegativeButton("No, no", new CancelOnClickListener());
				AlertDialog dialog = builder.create();
				dialog.show();
			}
			break;
			case DIALOG_WRONG:
			{
				// CreateoutAlterDialog
				Builder builder = new AlertDialog.Builder(this);
				builder.setMessage("Wrong answer");
				builder.setCancelable(true);
				//builder.setPositiveButton("I agree", new OkOnClickListener());
				builder.setNegativeButton("Again", new CancelOnClickListener());
				AlertDialog dialog = builder.create();
				dialog.show();
			}
			break;
		}

		return super.onCreateDialog(id);
	}

	private final class CancelOnClickListener implements DialogInterface.OnClickListener 
	{
		public void onClick(DialogInterface dialog, int which) 
		{
			Toast.makeText(getApplicationContext(), "Try again (don't forget to use the clues)",
					Toast.LENGTH_LONG).show();
		}
	}

	private final class OkOnClickListener implements DialogInterface.OnClickListener 
	{
		public void onClick(DialogInterface dialog, int which) 
		{
			// Lance la fermeture en cascade des activités de l'application
			setResult(RESULT_CLOSE_ALL);
			SolveActivity.this.finish();
		}
	}
}
