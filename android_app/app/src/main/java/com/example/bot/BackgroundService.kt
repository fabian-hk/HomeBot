package com.example.bot

import android.app.AlarmManager
import android.app.IntentService
import android.app.Service
import android.content.Intent
import android.content.IntentFilter
import android.net.ConnectivityManager
import android.net.wifi.WifiManager
import android.os.IBinder
import android.widget.Toast
import android.content.Context.ALARM_SERVICE
import android.app.PendingIntent
import android.app.job.JobParameters
import android.app.job.JobService
import android.content.Context
import android.util.Log


class BackgroundService : JobService() {

    override fun onStartJob(params: JobParameters?): Boolean {
        println("Service started")

        // register broadcast receiver
        val wifiConnectionBroadcast = WifiConnectionBroadcast()
        val filterWifiConnectionBroadcast = IntentFilter(ConnectivityManager.EXTRA_NETWORK).apply {
            addAction(WifiManager.NETWORK_STATE_CHANGED_ACTION)
        }
        registerReceiver(wifiConnectionBroadcast, filterWifiConnectionBroadcast)

        val alarmBroadcast = AlarmBroadcast()
        val filterAlarmBroadcast = IntentFilter(AlarmManager.ACTION_NEXT_ALARM_CLOCK_CHANGED).apply {
            addAction(AlarmManager.ACTION_NEXT_ALARM_CLOCK_CHANGED)
        }
        registerReceiver(alarmBroadcast, filterAlarmBroadcast)

        return true
    }

    override fun onStopJob(params: JobParameters?): Boolean {
        return true
    }
}
