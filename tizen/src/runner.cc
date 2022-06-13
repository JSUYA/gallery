#include "runner.h"

#include <Elementary.h>

#include "generated_plugin_registrant.h"

class App {
 public:
  ~App() {
    if (flutter_view) delete flutter_view;
    if (flutter_view2) delete flutter_view2;
  }
  
  Evas_Object *evas_image;
  ElmFlutterView *flutter_view;
  ElmFlutterView *flutter_view2;

  static void _btn_clicked(void *data, Evas_Object *obj EINA_UNUSED,
                           void *event_info EINA_UNUSED) {
    App *app = (App *)data;
    app->flutter_view->Resize(400, 600);
  }

  static void _btn_clicked2(void *data, Evas_Object *obj EINA_UNUSED,
                            void *event_info EINA_UNUSED) {
    App *app = (App *)data;
    app->flutter_view->Resize(700, 1000);
  }

  bool OnCreate() {
    Evas_Object *parent_window_ = elm_win_add(NULL, NULL, ELM_WIN_BASIC);
    elm_win_autodel_set(parent_window_, EINA_TRUE);
    elm_win_alpha_set(parent_window_, EINA_TRUE);

    Evas_Object *background_ = elm_bg_add(parent_window_);
    evas_object_size_hint_weight_set(background_, EVAS_HINT_EXPAND,
                                     EVAS_HINT_EXPAND);
    evas_object_color_set(background_, 255, 255, 255, 255);
    elm_win_resize_object_add(parent_window_, background_);

    Evas_Object *scr = elm_scroller_add(parent_window_);
    elm_scroller_bounce_set(scr, EINA_FALSE, EINA_TRUE);
    elm_scroller_policy_set(scr, ELM_SCROLLER_POLICY_OFF,
                            ELM_SCROLLER_POLICY_AUTO);
    evas_object_size_hint_weight_set(scr, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    elm_win_resize_object_add(parent_window_, scr);
    evas_object_show(scr);

    evas_object_show(background_);
    evas_object_show(parent_window_);

    Evas_Object *box = elm_box_add(parent_window_);
    evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_size_hint_min_set(box, 400, 400);
    elm_object_content_set(scr, box);

    Evas_Object *but = elm_button_add(box);
    elm_object_text_set(but, "Resize(400, 600)");
    evas_object_size_hint_weight_set(but, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_size_hint_align_set(but, EVAS_HINT_FILL, EVAS_HINT_FILL);
    evas_object_smart_callback_add(but, "clicked", _btn_clicked, this);

    elm_box_pack_end(box, but);
    evas_object_show(but);

    flutter_view = new ElmFlutterView(box, 720, 400);
    if (flutter_view->RunEngine()) {
      RegisterPlugins(flutter_view);
      evas_image = (Evas_Object *)flutter_view->evas_object();
      elm_box_pack_end(box, evas_image);
    }

    Evas_Object *button = elm_button_add(box);
    elm_object_text_set(button, "Resize(700, 1000)");
    evas_object_size_hint_weight_set(button, EVAS_HINT_EXPAND,
                                     EVAS_HINT_EXPAND);
    evas_object_size_hint_align_set(button, EVAS_HINT_FILL, EVAS_HINT_FILL);
    evas_object_smart_callback_add(button, "clicked", _btn_clicked2, this);
    evas_object_show(button);
    elm_box_pack_end(box, button);

    Evas_Object *entry = elm_entry_add(box);
    elm_entry_single_line_set(entry, EINA_TRUE);
    elm_entry_scrollable_set(entry, EINA_TRUE);
    elm_object_text_set(entry, "Entry Test");
    evas_object_size_hint_weight_set(entry, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_size_hint_align_set(entry, EVAS_HINT_FILL, EVAS_HINT_FILL);
    evas_object_show(entry);
    elm_box_pack_end(box, entry);

    flutter_view2 = new ElmFlutterView(box, 720, 400);
    if (flutter_view2->RunEngine()) {
      RegisterPlugins(flutter_view2);
      Evas_Object *evas_image2 = (Evas_Object *)flutter_view2->evas_object();
      elm_box_pack_end(box, evas_image2);
    }

    for (int i = 0; i < 10; i++) {
      Evas_Object *button = elm_button_add(box);
      elm_object_text_set(button, "Dummy");
      evas_object_size_hint_weight_set(button, EVAS_HINT_EXPAND,
                                       EVAS_HINT_EXPAND);
      evas_object_size_hint_align_set(button, EVAS_HINT_FILL, EVAS_HINT_FILL);
      evas_object_show(button);
      elm_box_pack_end(box, button);
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

  return ret;
}
