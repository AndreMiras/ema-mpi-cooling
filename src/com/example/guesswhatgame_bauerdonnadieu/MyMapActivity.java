package com.example.guesswhatgame_bauerdonnadieu;

/**
 * https://developers.google.com/maps/documentation/android/v1/hello-mapview
 */

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

import android.content.Context;
import android.content.Intent;
import android.graphics.drawable.Drawable;
import android.location.LocationManager;
import android.os.Bundle;
import android.view.Menu;
import android.view.View;

import com.google.android.maps.GeoPoint;
import com.google.android.maps.MapActivity;
import com.google.android.maps.MapController;
import com.google.android.maps.MapView;
import com.google.android.maps.MyLocationOverlay;
import com.google.android.maps.Overlay;
import com.google.android.maps.OverlayItem;

public class MyMapActivity extends MapActivity {

	private MapView mMapView;
	private MapController mController;
	private LocationManager locationManager;
	private MyItemizedOverlay itemizedOverlay;
	private MyLocationOverlay myLocationOverlay;
	private Random randomGenerator;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_map);
		setupMapView();
		loadMarkers();
		optimalMapSetup();
		setupLocationManager();
	}

	private void setupMapView() {
		mMapView = (MapView) findViewById(R.id.map_view);
		mMapView.setBuiltInZoomControls(true);
		mController = mMapView.getController();

		// sets the default marker for all overlay items
		Drawable drawable = this.getResources()
				.getDrawable(R.drawable.blue_dot);
		itemizedOverlay = new MyItemizedOverlay(drawable,
				this);
		List<Overlay> mapOverlays = mMapView.getOverlays();

		// sets myLocation
		myLocationOverlay = new MyLocationOverlay(
				getApplicationContext(),
				mMapView);
		myLocationOverlay.enableMyLocation();
		// centers the map on user location
		myLocationOverlay.runOnFirstFix(new Runnable() {
			public void run() {
				mController.animateTo(myLocationOverlay.getMyLocation());
				mController.setZoom(17);
			}
		});

		// adds itemizedOverlay and myLocationOverlay
		mapOverlays.add(itemizedOverlay);
		mapOverlays.add(myLocationOverlay);
		mMapView.invalidate(); // refreshes the map
	}

	private void optimalMapSetup()
	{
		mController.zoomToSpan(
				itemizedOverlay.getLatSpanE6(),
				itemizedOverlay.getLonSpanE6());
	}

	private void setupLocationManager()
	{
		// getSystemService
		// Get the location manager
	    locationManager = (LocationManager) getSystemService(Context.LOCATION_SERVICE);
	    /*
	    // Define the criteria how to select the locatioin provider -> use
	    // default
	    Criteria criteria = new Criteria();
	    provider = locationManager.getBestProvider(criteria, false);
		Location location = locationManager.getLastKnownLocation(provider);
		// Initialize the location fields
		if (location != null) {
			// System.out.println("Provider " + provider + " has been selected.");
			onLocationChanged(location);
		} else {
			// latituteField.setText("Location not available");
			// longitudeField.setText("Location not available");
		}
	     */
	}

	// TODO: we should be loading them from XML files or something like that
	private void loadMarkers() {
		ArrayList<String> markerDescriptions = new ArrayList<String>();
		int nbClues = 5;
		for (int i = 0; i < nbClues; i++) {
			markerDescriptions.add("Clue " + i);
		}
		addRandomMarkers(markerDescriptions);
	}

	private void addRandomMarkers(ArrayList<String> markerDescriptions) {
		randomGenerator = new Random();
		String markerTitle;
		int i = 0;
		for (String markerDescription : markerDescriptions) {
			markerTitle = "Clue " + i;
			addRandomMarker(markerTitle, markerDescription);
			i++;
		}
	}

	// TODO: Get available points from an XML file and "randomize" it
	/**
	 *
	 * @return a random GeoPoint that isn't already used
	 */
	private GeoPoint getRandomGeoPoint() {
		// generates random lat long
		// TODO: this is for debugging purposes, but the GeoPoint must be
		// physically reachable
		// int maxLat = 90;
		// int maxLng = 180;
		int franceLat = 46;
		int franceLng = 2;
		//
		int randomLat = getRandomInt(franceLat - 1, franceLat + 1);
		int randomLng = getRandomInt(franceLng - 1, franceLng + 1);
		// converts to micro dedegrees GeoPoint
		GeoPoint point = new GeoPoint((int) (randomLat * 1E6),
				(int) (randomLng * 1E6));

		return point;
	}

	private int getRandomInt(int min, int max) {
		return randomGenerator.nextInt(max - min + 1) + min;
	}

	private void addRandomMarker(String markerTitle, String markerDescription) {
		GeoPoint point = getRandomGeoPoint();
		OverlayItem overlayitem = new OverlayItem(point, markerTitle,
				markerDescription);
		itemizedOverlay.addOverlay(overlayitem);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.activity_map, menu);
		return true;
	}

	public void goToSolveActivityClick(View v) {
		Intent activity = new Intent(this, SolveActivity.class);
		startActivity(activity);
	}

	@Override
	protected boolean isRouteDisplayed() {
		return false;
	}

	/**
	 * Disables:
	 *	- myLocationOverlay
	 * 	- location updates requests
	 */
	@Override
	protected void onPause()
	{
		super.onPause();
		myLocationOverlay.disableMyLocation();
		locationManager.removeUpdates(itemizedOverlay);
	}

	/**
	 * Enables:
	 *	- myLocationOverlay
	 * 	- location updates requests
	 */
	@Override
	protected void onResume() {
		super.onResume();
		myLocationOverlay.enableMyLocation();

		// Starts listeners
		locationManager.requestLocationUpdates(LocationManager.GPS_PROVIDER, 0,
				1, itemizedOverlay);
	}
}
