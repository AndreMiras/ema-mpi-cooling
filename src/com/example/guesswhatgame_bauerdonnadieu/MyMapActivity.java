package com.example.guesswhatgame_bauerdonnadieu;

import java.util.List;

import android.content.Intent;
import android.graphics.drawable.Drawable;
import android.os.Bundle;
import android.view.Menu;
import android.view.View;

import com.google.android.maps.GeoPoint;
import com.google.android.maps.MapActivity;
import com.google.android.maps.MapController;
import com.google.android.maps.MapView;
import com.google.android.maps.Overlay;
import com.google.android.maps.OverlayItem;

public class MyMapActivity extends MapActivity {

	private MapView m_mapView;
	private MapController mController;
	// private MyItemizedOverlay images;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_map);
		setupMapView();
		loadMarkers();
	}

	private void setupMapView()
	{
		m_mapView = (MapView) findViewById(R.id.map_view);
        m_mapView.setBuiltInZoomControls(true);
		mController = m_mapView.getController();
        mController.animateTo(new GeoPoint(48625002, 2442962));
        mController.setZoom(18);
	}

	private void loadMarkers()
	{
        List<Overlay> mapOverlays = m_mapView.getOverlays();
        Drawable drawable = this.getResources().getDrawable(R.drawable.blue_dot);
        MyItemizedOverlay itemizedoverlay = new MyItemizedOverlay(drawable, this);

        GeoPoint point = new GeoPoint(48625119, 2442082);
        OverlayItem overlayitem = new OverlayItem(point, "Item 1", "Item 1 description");
        itemizedoverlay.addOverlay(overlayitem);
        mapOverlays.add(itemizedoverlay);
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
		startActivity(activity);
    }

	@Override
	protected boolean isRouteDisplayed() {
		return false;
	}

}
