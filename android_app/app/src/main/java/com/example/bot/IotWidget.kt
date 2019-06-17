package com.example.bot

import android.app.PendingIntent
import android.appwidget.AppWidgetManager
import android.appwidget.AppWidgetProvider
import android.content.Context
import android.content.Intent
import android.widget.RemoteViews

/**
 * Implementation of App Widget functionality.
 */
class IotWidget : AppWidgetProvider() {

    override fun onUpdate(context: Context, appWidgetManager: AppWidgetManager, appWidgetIds: IntArray) {
        // There may be multiple widgets active, so update all of them
        for (appWidgetId in appWidgetIds) {
            updateAppWidget(context, appWidgetManager, appWidgetId)
        }

    }

    override fun onEnabled(context: Context) {
        // Enter relevant functionality for when the first widget is created
    }

    override fun onDisabled(context: Context) {
        // Enter relevant functionality for when the last widget is disabled
    }

    companion object {

        internal fun updateAppWidget(
            context: Context, appWidgetManager: AppWidgetManager,
            appWidgetId: Int
        ) {

            // set action for button up
            val intentUp = Intent(context, ControlShadeBroadcast::class.java)
            intentUp.action = "com.example.bot.ControlShadeBroadcast"
            val listUp = ArrayList<Int>()
            listUp.add(0)
            listUp.add(20)
            listUp.add(0)
            intentUp.putExtra("values", listUp)

            val pendingUp = PendingIntent.getBroadcast(context, 0, intentUp, PendingIntent.FLAG_UPDATE_CURRENT)

            val views = RemoteViews(context.packageName, R.layout.iot_widget)
            views.setOnClickPendingIntent(R.id.move_up, pendingUp)

            appWidgetManager.updateAppWidget(appWidgetId, views)

            // set action for button down
            val intentDown = Intent(context, ControlShadeBroadcast::class.java)
            intentDown.action = "com.example.bot.ControlShadeBroadcast"
            val listDown = ArrayList<Int>()
            listDown.add(99)
            listDown.add(100)
            listDown.add(100)
            intentDown.putExtra("values", listDown)

            val pendingDown = PendingIntent.getBroadcast(context, 1, intentDown, PendingIntent.FLAG_UPDATE_CURRENT)

            views.setOnClickPendingIntent(R.id.move_down, pendingDown)

            appWidgetManager.updateAppWidget(appWidgetId, views)

        }
    }
}

