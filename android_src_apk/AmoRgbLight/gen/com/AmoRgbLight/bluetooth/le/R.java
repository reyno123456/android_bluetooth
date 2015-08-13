/* AUTO-GENERATED FILE.  DO NOT MODIFY.
 *
 * This class was automatically generated by the
 * aapt tool from the resource data it found.  It
 * should not be modified by hand.
 */

package com.AmoRgbLight.bluetooth.le;

public final class R {
    public static final class attr {
        /**  可滑动小球的颜色 
         <p>Must be a color value, in the form of "<code>#<i>rgb</i></code>", "<code>#<i>argb</i></code>",
"<code>#<i>rrggbb</i></code>", or "<code>#<i>aarrggbb</i></code>".
<p>This may also be a reference to a resource (in the form
"<code>@[<i>package</i>:]<i>type</i>:<i>name</i></code>") or
theme attribute (in the form
"<code>?[<i>package</i>:][<i>type</i>:]<i>name</i></code>")
containing a value of this type.
         */
        public static final int center_color=0x7f010002;
        /**  可滑动小球的半径 
         <p>Must be a dimension value, which is a floating point number appended with a unit such as "<code>14.5sp</code>".
Available units are: px (pixels), dp (density-independent pixels), sp (scaled pixels based on preferred font size),
in (inches), mm (millimeters).
<p>This may also be a reference to a resource (in the form
"<code>@[<i>package</i>:]<i>type</i>:<i>name</i></code>") or
theme attribute (in the form
"<code>?[<i>package</i>:][<i>type</i>:]<i>name</i></code>")
containing a value of this type.
         */
        public static final int center_radius=0x7f010001;
        /**  背景圆的半径 
         <p>Must be a dimension value, which is a floating point number appended with a unit such as "<code>14.5sp</code>".
Available units are: px (pixels), dp (density-independent pixels), sp (scaled pixels based on preferred font size),
in (inches), mm (millimeters).
<p>This may also be a reference to a resource (in the form
"<code>@[<i>package</i>:]<i>type</i>:<i>name</i></code>") or
theme attribute (in the form
"<code>?[<i>package</i>:][<i>type</i>:]<i>name</i></code>")
containing a value of this type.
         */
        public static final int circle_radius=0x7f010000;
    }
    public static final class drawable {
        public static final int ic_launcher=0x7f020000;
        public static final int piccolor=0x7f020001;
        public static final int reading__color_view__button=0x7f020002;
        public static final int reading__color_view__button_press=0x7f020003;
    }
    public static final class id {
        public static final int AmoMcu_taobao=0x7f06000e;
        public static final int about_text_help=0x7f060000;
        public static final int button_about=0x7f060004;
        public static final int color_picker_view=0x7f060001;
        public static final int connection_state=0x7f060010;
        public static final int data_value=0x7f060011;
        public static final int device_address=0x7f06000f;
        public static final int device_beacon_uuid=0x7f060014;
        public static final int device_major_minor=0x7f060016;
        public static final int device_name=0x7f060013;
        public static final int device_txPower_rssi=0x7f060015;
        public static final int gatt_services_list=0x7f060012;
        public static final int menu_connect=0x7f060018;
        public static final int menu_disconnect=0x7f060019;
        public static final int menu_refresh=0x7f060017;
        public static final int menu_scan=0x7f06001a;
        public static final int menu_stop=0x7f06001b;
        public static final int seekbar_blue=0x7f06000c;
        public static final int seekbar_brightness=0x7f060006;
        public static final int seekbar_green=0x7f06000a;
        public static final int seekbar_red=0x7f060008;
        public static final int togglebutton_flash=0x7f060003;
        public static final int togglebutton_onoff=0x7f060002;
        public static final int txt_brightness=0x7f060007;
        public static final int txt_color=0x7f060005;
        public static final int txt_color_blue=0x7f06000d;
        public static final int txt_color_green=0x7f06000b;
        public static final int txt_color_red=0x7f060009;
    }
    public static final class layout {
        public static final int about=0x7f030000;
        public static final int actionbar_indeterminate_progress=0x7f030001;
        public static final int amo_rgb_activity=0x7f030002;
        public static final int gatt_services_characteristics=0x7f030003;
        public static final int listitem_device=0x7f030004;
    }
    public static final class menu {
        public static final int gatt_services=0x7f050000;
        public static final int main=0x7f050001;
    }
    public static final class string {
        public static final int app_name=0x7f040000;
        public static final int app_version=0x7f040001;
        public static final int ble_not_supported=0x7f040002;
        public static final int connected=0x7f040007;
        public static final int device_rssi=0x7f040012;
        public static final int disconnected=0x7f040008;
        public static final int error_bluetooth_not_supported=0x7f04000a;
        public static final int label_data=0x7f040003;
        public static final int label_device_address=0x7f040004;
        public static final int label_state=0x7f040005;
        /**  Menu items 
         */
        public static final int menu_connect=0x7f04000e;
        public static final int menu_disconnect=0x7f04000f;
        public static final int menu_scan=0x7f040010;
        public static final int menu_stop=0x7f040011;
        public static final int no_data=0x7f040006;
        public static final int text_detail=0x7f040013;
        public static final int title_devices=0x7f040009;
        public static final int unknown_characteristic=0x7f04000c;
        public static final int unknown_device=0x7f04000b;
        public static final int unknown_service=0x7f04000d;
    }
    public static final class styleable {
        /** Attributes that can be used with a color_picker.
           <p>Includes the following attributes:</p>
           <table>
           <colgroup align="left" />
           <colgroup align="left" />
           <tr><th>Attribute</th><th>Description</th></tr>
           <tr><td><code>{@link #color_picker_center_color com.AmoRgbLight.bluetooth.le:center_color}</code></td><td> 可滑动小球的颜色 </td></tr>
           <tr><td><code>{@link #color_picker_center_radius com.AmoRgbLight.bluetooth.le:center_radius}</code></td><td> 可滑动小球的半径 </td></tr>
           <tr><td><code>{@link #color_picker_circle_radius com.AmoRgbLight.bluetooth.le:circle_radius}</code></td><td> 背景圆的半径 </td></tr>
           </table>
           @see #color_picker_center_color
           @see #color_picker_center_radius
           @see #color_picker_circle_radius
         */
        public static final int[] color_picker = {
            0x7f010000, 0x7f010001, 0x7f010002
        };
        /**
          <p>
          @attr description
           可滑动小球的颜色 


          <p>Must be a color value, in the form of "<code>#<i>rgb</i></code>", "<code>#<i>argb</i></code>",
"<code>#<i>rrggbb</i></code>", or "<code>#<i>aarrggbb</i></code>".
<p>This may also be a reference to a resource (in the form
"<code>@[<i>package</i>:]<i>type</i>:<i>name</i></code>") or
theme attribute (in the form
"<code>?[<i>package</i>:][<i>type</i>:]<i>name</i></code>")
containing a value of this type.
          <p>This is a private symbol.
          @attr name com.AmoRgbLight.bluetooth.le:center_color
        */
        public static final int color_picker_center_color = 2;
        /**
          <p>
          @attr description
           可滑动小球的半径 


          <p>Must be a dimension value, which is a floating point number appended with a unit such as "<code>14.5sp</code>".
Available units are: px (pixels), dp (density-independent pixels), sp (scaled pixels based on preferred font size),
in (inches), mm (millimeters).
<p>This may also be a reference to a resource (in the form
"<code>@[<i>package</i>:]<i>type</i>:<i>name</i></code>") or
theme attribute (in the form
"<code>?[<i>package</i>:][<i>type</i>:]<i>name</i></code>")
containing a value of this type.
          <p>This is a private symbol.
          @attr name com.AmoRgbLight.bluetooth.le:center_radius
        */
        public static final int color_picker_center_radius = 1;
        /**
          <p>
          @attr description
           背景圆的半径 


          <p>Must be a dimension value, which is a floating point number appended with a unit such as "<code>14.5sp</code>".
Available units are: px (pixels), dp (density-independent pixels), sp (scaled pixels based on preferred font size),
in (inches), mm (millimeters).
<p>This may also be a reference to a resource (in the form
"<code>@[<i>package</i>:]<i>type</i>:<i>name</i></code>") or
theme attribute (in the form
"<code>?[<i>package</i>:][<i>type</i>:]<i>name</i></code>")
containing a value of this type.
          <p>This is a private symbol.
          @attr name com.AmoRgbLight.bluetooth.le:circle_radius
        */
        public static final int color_picker_circle_radius = 0;
    };
}
