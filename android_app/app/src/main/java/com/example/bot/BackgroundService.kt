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



        return true
    }

    override fun onStopJob(params: JobParameters?): Boolean {
        return true
    }
}
