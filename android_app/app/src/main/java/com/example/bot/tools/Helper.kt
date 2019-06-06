package com.example.bot.tools

import android.content.Context
import android.net.wifi.SupplicantState
import android.net.wifi.WifiManager
import com.example.bot.R

fun getNetworkBssid(context: Context) : String? {
    var wifiManager = context.getSystemService(Context.WIFI_SERVICE) as WifiManager

    var wifiInfo = wifiManager.connectionInfo
    if (wifiInfo.supplicantState == SupplicantState.COMPLETED) {
        return wifiInfo.bssid
    }
    return null;
}

fun getSharedPreferenceString(context: Context, key: String) : String? {
    val sharedPref = context.getSharedPreferences(context.getString(R.string.preference_file), Context.MODE_PRIVATE)
    return sharedPref.getString(key, null)
}

fun getSharedPreferenceInt(context: Context, key: String) : Int {
    val sharedPref = context.getSharedPreferences(context.getString(R.string.preference_file), Context.MODE_PRIVATE)
    return sharedPref.getInt(key, -1)
}