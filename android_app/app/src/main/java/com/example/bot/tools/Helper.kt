package com.example.bot.tools

import android.content.Context
import android.net.wifi.SupplicantState
import android.net.wifi.WifiManager
import android.widget.Toast

import io.grpc.ManagedChannelBuilder

import java.lang.Exception

import com.example.bot.R
import com.example.bot.grpc_proto.IOTGrpc
import com.example.bot.grpc_proto.Schedule


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

fun getSharedPreferenceLong(context: Context, key: String) : Long {
    val sharedPref = context.getSharedPreferences(context.getString(R.string.preference_file), Context.MODE_PRIVATE)
    return sharedPref.getLong(key, -1)
}

fun setSharedPreferenceLong(context: Context, key: Int, value: Long) {
    val sharedPref = context.getSharedPreferences(
        context.getString(R.string.preference_file),
        Context.MODE_PRIVATE
    )

    with(sharedPref.edit()) {
        putLong(context.getString(key), value)
        apply()
    }
}

fun sendWindowShadeRequest(context: Context, id: String, time: Long, pos: ArrayList<Int>) {
    try {
        var ip = getSharedPreferenceString(context, context.getString(R.string.iot_ip))
        var mChannel = ManagedChannelBuilder.forAddress(ip, 1616).usePlaintext().build()
        var blockingStub = IOTGrpc.newBlockingStub(mChannel)

        var sched = Schedule.newBuilder()
            .setId(id)
            .setTime(time)
            .addAllPositions(pos.toMutableList())
            .build()

        var status = blockingStub.setShadeSchedule(sched)
        Toast.makeText(context, "Status: " + status.status, Toast.LENGTH_SHORT).show()
        println("Status: " + status.status)
        mChannel.shutdownNow()
    } catch (e: Exception) {
        e.printStackTrace()
        Toast.makeText(context, "Status: 1", Toast.LENGTH_SHORT).show()
    }
}

fun checkNetwork(context: Context): Boolean {
    val _bssid = getNetworkBssid(context)
    var bssid = getSharedPreferenceString(context, context.getString(R.string.bssid))

    if (_bssid != null && bssid != null && bssid!!.compareTo(_bssid!!) == 0) {
        return true
    }
    return false
}