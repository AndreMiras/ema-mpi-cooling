package com.example.guesswhatgame_bauerdonnadieu;
/**
 * https://developers.google.com/maps/documentation/android/v1/hello-mapview
 */

import java.util.ArrayList;

import android.app.AlertDialog;
import android.content.Context;
import android.graphics.drawable.Drawable;

import com.google.android.maps.ItemizedOverlay;
import com.google.android.maps.OverlayItem;

public class MyItemizedOverlay extends ItemizedOverlay {

	private ArrayList<OverlayItem> mOverlays = new ArrayList<OverlayItem>();
	Context mContext;

	public MyItemizedOverlay(Drawable defaultMarker) {
		super(boundCenterBottom(defaultMarker));
	}
	
	public MyItemizedOverlay(Drawable defaultMarker, Context context) {
		  super(boundCenterBottom(defaultMarker));
		  mContext = context;
		}

	public void addOverlay(OverlayItem overlay) {
	    mOverlays.add(overlay);
	    populate();
	}

	public ArrayList<OverlayItem> getOverLays()
	{
		return mOverlays;
	}

	@Override
	protected boolean onTap(int index) {
	  return onTapPopup(2);
	}

	private boolean onTapPopup(int index) {
		OverlayItem item = mOverlays.get(index);
		AlertDialog.Builder dialog = new AlertDialog.Builder(mContext);
		dialog.setTitle(item.getTitle());
		dialog.setMessage(item.getSnippet());
		dialog.show();
		return true;
	}

	// TODO: crashing: You are only allowed to have a single MapView in a
	// MapActivity
	/*
	private boolean onTapPopup2(int index) {
		OverlayItem item = mOverlays.get(index);
		LayoutInflater inflater = (LayoutInflater) mContext
				.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		// TODO: is this the correct way to do to get the map view?
		MapView map = (MapView) ((MapActivity) mContext)
		.findViewById(R.id.map_view);
		View popUp = inflater.inflate(R.layout.activity_map, map, false);
		MapView.LayoutParams mapParams = new MapView.LayoutParams(
				ViewGroup.LayoutParams.WRAP_CONTENT,
				ViewGroup.LayoutParams.WRAP_CONTENT, item.getPoint(), 0, 0,
				MapView.LayoutParams.BOTTOM_CENTER);
		map.addView(popUp, mapParams);
		return true;
	}
	*/


	@Override
	protected OverlayItem createItem(int i) {
		return mOverlays.get(i);
	}

	@Override
	public int size() {
		return mOverlays.size();
	}

}
