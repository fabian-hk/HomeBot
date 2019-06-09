package com.example.bot

import android.app.AlarmManager
import android.content.BroadcastReceiver
import android.content.Context
import android.content.Intent

import com.example.bot.tools.*


class AlarmBroadcast : BroadcastReceiver() {

    override fun onReceive(context: Context?, intent: Intent?) {
        if (checkNetwork(context!!)) {
            var alarmManager: AlarmManager = context.getSystemService(Context.ALARM_SERVICE) as AlarmManager
            if (alarmManager.nextAlarmClock != null) {
                var time = alarmManager.nextAlarmClock.triggerTime // time in millisecond since epoch
                time -= 900000 // subtract 15 minutes

                setSharedPreferenceLong(context, R.string.time, time)

                var pos = ArrayList<Int>()
                pos.add(getSharedPreferenceInt(context, context.getString(R.string.sh0)))
                pos.add(getSharedPreferenceInt(context, context.getString(R.string.sh1)))
                pos.add(getSharedPreferenceInt(context, context.getString(R.string.sh2)))

                sendWindowShadeRequest(
                    context,
                    getSharedPreferenceString(context, context.getString(R.string.sh_id))!!,
                    time,
                    pos
                )

            }
        }
    }
}