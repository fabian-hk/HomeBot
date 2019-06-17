package com.example.bot

import android.app.AlarmManager
import android.app.job.JobInfo
import android.app.job.JobScheduler
import android.appwidget.AppWidgetManager
import android.content.ComponentName
import android.content.Context
import android.content.Intent
import android.content.IntentFilter
import android.net.ConnectivityManager
import android.net.wifi.WifiManager
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.widget.TextView
import android.view.View
import android.widget.EditText
import android.widget.Toast

import java.lang.NumberFormatException

import com.example.bot.tools.getNetworkBssid
import com.example.bot.tools.getSharedPreferenceInt
import com.example.bot.tools.getSharedPreferenceString


class MainActivity : AppCompatActivity() {

    private lateinit var bssidView: TextView
    private lateinit var ipEditText: EditText
    private lateinit var shadeIdEditText: EditText
    private lateinit var shade0EditText: EditText
    private lateinit var shade1EditText: EditText
    private lateinit var shade2EditText: EditText

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        // register broadcast receiver
        val wifiConnectionBroadcast = WifiConnectionBroadcast()
        val filterWifiConnectionBroadcast = IntentFilter(ConnectivityManager.EXTRA_NETWORK).apply {
            addAction(WifiManager.NETWORK_STATE_CHANGED_ACTION)
        }
        registerReceiver(wifiConnectionBroadcast, filterWifiConnectionBroadcast)

        // initialize GUI components
        bssidView = findViewById(R.id.ssid);
        ipEditText = findViewById(R.id.iot_ip)

        shadeIdEditText = findViewById(R.id.id)
        shade0EditText = findViewById(R.id.shade0)
        shade1EditText = findViewById(R.id.shade1)
        shade2EditText = findViewById(R.id.shade2)

        // init GUI with saved values
        ipEditText.setText(getSharedPreferenceString(applicationContext, getString(R.string.iot_ip)))

        shadeIdEditText.setText(getSharedPreferenceString(applicationContext, getString(R.string.sh_id)))
        shade0EditText.setText(getSharedPreferenceInt(applicationContext, getString(R.string.sh0)).toString())
        shade1EditText.setText(getSharedPreferenceInt(applicationContext, getString(R.string.sh1)).toString())
        shade2EditText.setText(getSharedPreferenceInt(applicationContext, getString(R.string.sh2)).toString())
    }

    override fun onResume() {
        super.onResume()
        bssidView.text = getNetworkBssid(applicationContext)
    }

    /**
     * Save configuration to shared preference
     */
    public fun saveNetwork(view: View) {
        var error = false

        var strSh0 = shade0EditText.text.toString()
        var strSh1 = shade1EditText.text.toString()
        var strSh2 = shade2EditText.text.toString()

        if (strSh0.equals("") || strSh1.equals("") || strSh2.equals("")) {
            error = true
        }

        if (!error) {
            var sh0 = 0
            var sh1 = 0
            var sh2 = 0
            try {
                sh0 = Integer.valueOf(shade0EditText.text.toString())
                sh1 = Integer.valueOf(shade1EditText.text.toString())
                sh2 = Integer.valueOf(shade2EditText.text.toString())
            } catch (e: NumberFormatException) {
                error = true
            }


            if (!error && sh0 in IntRange(0, 100) && sh1 in IntRange(0, 100) && sh2 in IntRange(0, 100)) {
                val sharedPref =
                    applicationContext.getSharedPreferences(getString(R.string.preference_file), Context.MODE_PRIVATE)
                with(sharedPref.edit()) {
                    putString(getString(R.string.sh_id), shadeIdEditText.text.toString())
                    putString(getString(R.string.bssid), bssidView.text.toString())
                    putString(getString(R.string.iot_ip), ipEditText.text.toString())
                    putInt(getString(R.string.sh0), sh0)
                    putInt(getString(R.string.sh1), sh1)
                    putInt(getString(R.string.sh2), sh2)
                    apply()
                }
                Toast.makeText(applicationContext, "Saved config", Toast.LENGTH_SHORT).show()
            } else {
                error = true
            }
        }
        if (error) {
            Toast.makeText(applicationContext, "Wrong input", Toast.LENGTH_SHORT).show()
        }
    }
}
