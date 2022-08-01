#include "runner.h"

#include <Elementary.h>

#include "generated_plugin_registrant.h"

class App {
 public:
  bool visibility = true;
  bool changeSize = true;
  bool changeWidget = true;
  ElmFlutterView *flutter_view;
  Evas_Object *evas_image;
  Evas_Object *box2;
  Evas_Object *gl;
  Evas_Object *nf;
  Evas_Object *flutter_box;
  Evas_Object *gl_box = NULL;

  ~App() {
    if (flutter_view) delete flutter_view;
  }

  static void _response_cb(void *data, Evas_Object *obj EINA_UNUSED,
                           void *event_info EINA_UNUSED) {
    elm_popup_dismiss((Evas_Object *)data);
  }

  static void _btn_clicked(void *data, Evas_Object *obj EINA_UNUSED,
                           void *event_info EINA_UNUSED) {
    Evas_Object *win = (Evas_Object *)data;
    Evas_Object *popup = elm_popup_add(win);
    elm_object_text_set(popup, "Flutter!!!!!!");

    Evas_Object *btn = elm_button_add(popup);
    elm_object_style_set(btn, "popup");
    elm_object_text_set(btn, "BUTTON");
    elm_object_part_content_set(popup, "button1", btn);
    evas_object_smart_callback_add(btn, "clicked", _response_cb, popup);

    evas_object_smart_callback_add(popup, "block,clicked", _response_cb, popup);
    evas_object_smart_callback_add(popup, "dismissed", _response_cb, NULL);
    evas_object_show(popup);
  }

  static void table_del_cb(void *data, Evas *e, Evas_Object *obj,
                           void *event_info) {
    elm_table_clear(obj, EINA_TRUE);
  }

  static Evas_Object *widget_min_set(Evas_Object *obj, Evas_Object *parent,
                                     Evas_Coord w, Evas_Coord h) {
    Evas_Object *table, *rect;

    table = elm_table_add(parent);

    rect = evas_object_rectangle_add(evas_object_evas_get(table));
    evas_object_size_hint_min_set(rect, w, h);
    evas_object_size_hint_weight_set(rect, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_size_hint_align_set(rect, EVAS_HINT_FILL, EVAS_HINT_FILL);
    elm_table_pack(table, rect, 0, 0, 1, 1);

    evas_object_size_hint_weight_set(obj, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_size_hint_align_set(obj, EVAS_HINT_FILL, EVAS_HINT_FILL);
    elm_table_pack(table, obj, 0, 0, 1, 1);

    return table;
  }

  static void _btn_elm_clicked(void *data, Evas_Object *obj EINA_UNUSED,
                               void *event_info EINA_UNUSED) {
    App *a = (App *)data;
    Evas_Object *image = a->evas_image;
    Evas_Object *box2 = a->box2;
    Evas_Object *gl = a->gl;
    Evas_Object *nf = a->nf;
    Evas_Object *flutter_box = a->flutter_box;
    Evas_Object *gl_box = a->gl_box;

    if (a->changeWidget) {
      elm_object_content_unset(nf);
      evas_object_hide(image);
      a->changeWidget = false;

      if (!gl_box) {
        gl_box = elm_box_add(nf);
        evas_object_size_hint_weight_set(gl_box, EVAS_HINT_EXPAND,
                                         EVAS_HINT_EXPAND);

        Evas_Object *scr = elm_scroller_add(gl_box);
        elm_scroller_bounce_set(scr, EINA_TRUE, EINA_FALSE);
        elm_scroller_policy_set(scr, ELM_SCROLLER_POLICY_AUTO,
                                ELM_SCROLLER_POLICY_OFF);
        evas_object_size_hint_weight_set(scr, EVAS_HINT_EXPAND,
                                         EVAS_HINT_EXPAND);
        evas_object_show(scr);

        Evas_Object *table = widget_min_set(scr, gl_box, ELM_SCALE_SIZE(800),
                                            ELM_SCALE_SIZE(450));
        evas_object_event_callback_add(table, EVAS_CALLBACK_DEL, table_del_cb,
                                       NULL);
        evas_object_show(table);
        elm_box_pack_end(gl_box, table);

        Evas_Object *boxsub = elm_box_add(scr);
        evas_object_size_hint_weight_set(boxsub, EVAS_HINT_EXPAND,
                                         EVAS_HINT_FILL);
        evas_object_size_hint_align_set(boxsub, EVAS_HINT_FILL, EVAS_HINT_FILL);
        elm_box_horizontal_set(boxsub, EINA_TRUE);
        evas_object_show(boxsub);
        elm_object_content_set(scr, boxsub);
        for (int i = 0; i < 20; i++) {
          Evas_Object *image = elm_image_add(boxsub);

          evas_object_size_hint_weight_set(image, EVAS_HINT_EXPAND,
                                           EVAS_HINT_FILL);
          evas_object_size_hint_align_set(image, EVAS_HINT_FILL,
                                          EVAS_HINT_FILL);
          char buf[255];
          snprintf(buf, 255,
                   "/opt/usr/globalapps/com.example.test_cpp_3/res/"
                   "flutter_assets/assets/images/movies/movie_%d.jpg",
                   i % 6 + 1);

          elm_image_file_set(image, buf, NULL);
          elm_image_aspect_fixed_set(image, true);
          elm_box_pack_end(boxsub, image);
          evas_object_size_hint_min_set(image, ELM_SCALE_SIZE(300),
                                        ELM_SCALE_SIZE(400));
          evas_object_show(image);
        }
        evas_object_show(gl_box);
      }

      elm_object_content_set(nf, gl_box);
      evas_object_show(gl_box);
    }
  }

  static void _btn_flutter_clicked(void *data, Evas_Object *obj EINA_UNUSED,
                                   void *event_info EINA_UNUSED) {
    App *a = (App *)data;
    Evas_Object *image = a->evas_image;
    Evas_Object *box2 = a->box2;
    Evas_Object *gl = a->gl;
    Evas_Object *nf = a->nf;
    Evas_Object *flutter_box = a->flutter_box;

    if (!a->changeWidget) {
      evas_object_show(image);
      elm_object_content_set(nf, flutter_box);

      a->changeWidget = true;
    }
  }

  bool OnCreate() {
    visibility = true;

    Evas_Object *parent_window_ = elm_win_add(NULL, NULL, ELM_WIN_BASIC);
    elm_win_autodel_set(parent_window_, EINA_TRUE);
    elm_win_alpha_set(parent_window_, EINA_TRUE);

    Evas_Object *background_ = elm_bg_add(parent_window_);
    evas_object_size_hint_weight_set(background_, EVAS_HINT_EXPAND,
                                     EVAS_HINT_EXPAND);
    evas_object_color_set(background_, 255, 255, 255, 255);
    elm_win_resize_object_add(parent_window_, background_);

    Evas_Object *scr = elm_scroller_add(parent_window_);
    elm_scroller_bounce_set(scr, EINA_FALSE, EINA_FALSE);
    elm_scroller_policy_set(scr, ELM_SCROLLER_POLICY_OFF,
                            ELM_SCROLLER_POLICY_AUTO);
    evas_object_size_hint_weight_set(scr, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    elm_win_resize_object_add(parent_window_, scr);
    evas_object_show(scr);

    evas_object_show(background_);
    evas_object_show(parent_window_);

    Evas_Object *box = elm_box_add(parent_window_);
    evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

    elm_object_content_set(scr, box);

    Evas_Object *boxsub = elm_box_add(box);
    evas_object_size_hint_weight_set(boxsub, EVAS_HINT_EXPAND, EVAS_HINT_FILL);
    evas_object_size_hint_align_set(boxsub, EVAS_HINT_FILL, EVAS_HINT_FILL);
    elm_box_horizontal_set(boxsub, EINA_TRUE);
    evas_object_show(boxsub);
    elm_box_pack_end(box, boxsub);

    Evas_Object *button = elm_button_add(boxsub);
    elm_object_text_set(button, "FlutterView Tab");
    evas_object_size_hint_weight_set(button, EVAS_HINT_EXPAND,
                                     EVAS_HINT_EXPAND);
    evas_object_size_hint_align_set(button, EVAS_HINT_FILL, EVAS_HINT_FILL);
    evas_object_show(button);
    elm_box_pack_end(boxsub, button);
    evas_object_smart_callback_add(button, "clicked", _btn_flutter_clicked,
                                   this);

    Evas_Object *button2 = elm_button_add(boxsub);
    elm_object_text_set(button2, "Elementary Tab");
    evas_object_size_hint_weight_set(button2, EVAS_HINT_EXPAND,
                                     EVAS_HINT_EXPAND);
    evas_object_size_hint_align_set(button2, EVAS_HINT_FILL, EVAS_HINT_FILL);
    evas_object_smart_callback_add(button2, "clicked", _btn_elm_clicked, this);
    evas_object_show(button2);
    elm_box_pack_end(boxsub, button2);

    Evas_Object *button3 = elm_button_add(boxsub);
    elm_object_text_set(button3, "Elm Popup Test");
    evas_object_size_hint_weight_set(button3, EVAS_HINT_EXPAND,
                                     EVAS_HINT_EXPAND);
    evas_object_size_hint_align_set(button3, EVAS_HINT_FILL, EVAS_HINT_FILL);
    evas_object_show(button3);
    elm_box_pack_end(boxsub, button3);

    evas_object_smart_callback_add(button3, "clicked", _btn_clicked,
                                   parent_window_);

    nf = elm_naviframe_add(box);
    evas_object_size_hint_weight_set(nf, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_size_hint_align_set(nf, EVAS_HINT_FILL, EVAS_HINT_FILL);

    Evas_Object *nf_it = elm_naviframe_item_push(nf, "Flutter View Demo", NULL,
                                                 NULL, NULL, "default");
    evas_object_show(nf);
    elm_box_pack_end(box, nf);

    flutter_box = elm_box_add(nf_it);
    evas_object_size_hint_weight_set(flutter_box, EVAS_HINT_EXPAND,
                                     EVAS_HINT_EXPAND);
    elm_box_horizontal_set(flutter_box, EINA_TRUE);
    evas_object_show(flutter_box);
    elm_object_content_set(nf, flutter_box);
    flutter_view = new ElmFlutterView(flutter_box, 1920, 950);
    if (flutter_view->RunEngine()) {
      RegisterPlugins(flutter_view);
      evas_image = (Evas_Object *)flutter_view->evas_object();
      evas_object_show(evas_image);
      elm_box_pack_end(flutter_box, evas_image);
    }

    return flutter_view->IsRunning();
  }
};

int main(int argc, char *argv[]) {
  App app;

  ui_app_lifecycle_callback_s lifecycle_cb = {};
  lifecycle_cb.create = [](void *data) -> bool {
    auto *app = reinterpret_cast<App *>(data);
    return app->OnCreate();
  };

  int ret = ui_app_main(argc, argv, &lifecycle_cb, (void *)&app);
  if (ret != APP_ERROR_NONE) {
    // TizenLog::Error("Could not launch an application. (%d)", ret);
  }
  return ret;
}
