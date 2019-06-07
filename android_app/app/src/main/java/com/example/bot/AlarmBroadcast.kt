package com.example.bot

import android.app.AlarmManager
import android.content.BroadcastReceiver
import android.content.Context
import android.content.Intent
import android.widget.Toast
import java.lang.Exception

import io.grpc.ManagedChannelBuilder

import com.example.bot.grpc_proto.IOTGrpc
import com.example.bot.grpc_proto.Schedule
import com.example.bot.tools.getNetworkBssid
import com.example.bot.tools.getSharedPreferenceInt
import com.example.bot.tools.getSharedPreferenceString


class AlarmBroadcast : BroadcastReceiver() {

    override fun onReceive(context: Context?, intent: Intent?) {
        if (checkNetwork(context!!)) {
            var alarmManager: AlarmManager = context.getSystemService(Context.ALARM_SERVICE) as AlarmManager
            if (alarmManager.nextAlarmClock != null) {
                var time = alarmManager.nextAlarmClock.triggerTime // time in millisecond since epoch
                time -= 1800000 // subtract half an hour

                Toast.makeText(context, "Set alarm to: " + time, Toast.LENGTH_SHORT).show()

                try {
                    var ip = getSharedPreferenceString(context, context.getString(R.string.iot_ip))
                    var mChannel = ManagedChannelBuilder.forAddress(ip, 1616).usePlaintext().build()
                    var blockingStub = IOTGrpc.newBlockingStub(mChannel)
                    var pos = ArrayList<Int>()
                    pos.add(getSharedPreferenceInt(context, context.getString(R.string.sh0))!!)
                    pos.add(getSharedPreferenceInt(context, context.getString(R.string.sh1))!!)
                    pos.add(getSharedPreferenceInt(context, context.getString(R.string.sh2))!!)
                    var sched = Schedule.newBuilder()
                        .setId(getSharedPreferenceString(context, context.getString(R.string.sh_id)))
                        .setTime(time)
                        .addAllPositions(pos.toMutableList())
                        .build()

                    var status = blockingStub.setShadeSchedule(sched)
                    println("Status: " + status.status)
                    mChannel.shutdownNow()
                } catch (e: Exception) {
                    e.printStackTrace()
                }
            }
        }
    }

    private fun checkNetwork(context: Context): Boolean {
        val _bssid = getNetworkBssid(context)
        var bssid = getSharedPreferenceString(context, context.getString(R.string.bssid))

        if (bssid!!.compareTo(_bssid!!) == 0) {
            return true
        }
        return false
    }

}