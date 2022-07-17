package com.foxit.flutterfoxitpdf;

import androidx.annotation.NonNull;
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;

import com.foxit.sdk.common.Constants;
import com.foxit.sdk.common.Library;

import io.flutter.embedding.engine.plugins.FlutterPlugin;
import io.flutter.embedding.engine.plugins.activity.ActivityAware;
import io.flutter.embedding.engine.plugins.activity.ActivityPluginBinding;
import io.flutter.plugin.common.MethodCall;
import io.flutter.plugin.common.MethodChannel;
import io.flutter.plugin.common.MethodChannel.MethodCallHandler;
import io.flutter.plugin.common.MethodChannel.Result;

/** FlutterfoxitpdfPlugin */
public class FlutterfoxitpdfPlugin implements FlutterPlugin, MethodCallHandler, ActivityAware {
  /// The MethodChannel that will the communication between Flutter and native Android
  ///
  /// This local reference serves to register the plugin with the Flutter Engine and unregister it
  /// when the Flutter Engine is detached from the Activity
  // private ActivityPluginBinding _activityBinding;
  private Activity mActivity;
  private MethodChannel channel;
  private int errorCode = Constants.e_ErrUnknown;


  @Override
  public void onAttachedToEngine(@NonNull FlutterPluginBinding flutterPluginBinding) {
    channel = new MethodChannel(flutterPluginBinding.getBinaryMessenger(), "flutterfoxitpdf");
    channel.setMethodCallHandler(this);

  }
  @Override
  public void onAttachedToActivity(ActivityPluginBinding binding) {
    mActivity = binding.getActivity();
  }


  @Override
  public void   onDetachedFromActivity() {
    mActivity = null;
  }

  @Override
  public void   onReattachedToActivityForConfigChanges​(ActivityPluginBinding binding) {
    mActivity =  binding.getActivity();
  }

  @Override
  public void   onDetachedFromActivityForConfigChanges() {
    mActivity = null;
  }

  @Override
  public void onMethodCall(@NonNull MethodCall call, @NonNull Result result) {
    if (call.method.equals("getPlatformVersion")) {
      result.success("Android " + android.os.Build.VERSION.RELEASE);
    }  else if (call.method.equals("initialize")) {
      initialize(call, result);
    } else if (call.method.equals("openDocument")) {
      openDocument(call, result);
    } else {
      result.notImplemented();
    }
  }

  @Override
  public void onDetachedFromEngine(@NonNull FlutterPluginBinding binding) {
    channel.setMethodCallHandler(null);
  }

  private void initialize(MethodCall call, Result result) {
    String sn = call.argument("sn");
    String key = call.argument("key");
    errorCode = Library.initialize(sn, key);
    result.success(errorCode);
  }

  private void openDocument(MethodCall call, Result result) {
    if (errorCode != Constants.e_ErrSuccess) {
      result.error("" + errorCode,"Failed to initialize Foxit Library", errorCode);
      return;
    }
    String path = call.argument("path");
    String password = call.argument("password");

    if (path == null || path.trim().length() < 1) {
      result.error("" + Constants.e_ErrParam,"Invalid path", Constants.e_ErrParam);
      return;
    }

    if (mActivity == null) {
      result.error("-1","The Activity is null", -1);
      return;
    }

    Intent intent = new Intent(mActivity, PDFReaderActivity.class);
    Bundle bundle = new Bundle();
    bundle.putString("path", path);
    bundle.putString("password", password);
    intent.putExtras(bundle);

    mActivity.startActivity(intent);
    result.success(true);
  }
}
