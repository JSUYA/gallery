#include "runner.h"

#include <Elementary.h>

#include "generated_plugin_registrant.h"

class App
{
public:
  bool OnCreate()
  {
    Evas_Object *win = elm_win_add(NULL, NULL, ELM_WIN_BASIC);
    elm_win_autodel_set(win, EINA_TRUE);
    elm_win_alpha_set(win, EINA_TRUE);

    Evas_Object *background_ = elm_bg_add(win);
    evas_object_size_hint_weight_set(background_, EVAS_HINT_EXPAND,
                                     EVAS_HINT_EXPAND);
    evas_object_color_set(background_, 255, 255, 255, 255);
    elm_win_resize_object_add(win, background_);

    Evas_Object *scr = elm_scroller_add(win);
    elm_scroller_bounce_set(scr, EINA_FALSE, EINA_TRUE);
    elm_scroller_policy_set(scr, ELM_SCROLLER_POLICY_OFF,
                            ELM_SCROLLER_POLICY_AUTO);
    evas_object_size_hint_weight_set(scr, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    elm_win_resize_object_add(win, scr);
    evas_object_show(scr);

    evas_object_show(background_);
    evas_object_show(win);

    Evas_Object *box = elm_box_add(win);
    evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_size_hint_min_set(box, 400, 400);
    elm_object_content_set(scr, box);

    Evas_Object *but = elm_button_add(box);
    elm_object_text_set(but, "TEST");
    evas_object_size_hint_weight_set(but, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_size_hint_align_set(but, EVAS_HINT_FILL, EVAS_HINT_FILL);
    elm_box_pack_end(box, but);
    evas_object_show(but);

    // Create FlutterEngine
    auto engine = FlutterEngine::Create();

    // Create ElmFlutterView
    auto flutter_view = new ElmFlutterView(box, 720, 800);
    flutter_view->SetEngine(std::move(engine));

    if (flutter_view->RunEngine())
    {
      RegisterPlugins(flutter_view->engine());
      auto evas_object =
          static_cast<Evas_Object *>(flutter_view->evas_object());
      elm_box_pack_end(box, evas_object); // Set the evas_object drawn to
                                          // flutter to the content of the box.
    }

    Evas_Object *but2 = elm_button_add(box);
    elm_object_text_set(but2, "TEEST");
    evas_object_size_hint_weight_set(but2, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_size_hint_align_set(but2, EVAS_HINT_FILL, EVAS_HINT_FILL);
    evas_object_show(but2);
    elm_box_pack_end(box, but2);

    return true;
  }
};

int main(int argc, char *argv[])
{
  App app;

  ui_app_lifecycle_callback_s lifecycle_cb = {};
  lifecycle_cb.create = [](void *data) -> bool
  {
    auto *app = reinterpret_cast<App *>(data);
    return app->OnCreate();
  };

  int ret = ui_app_main(argc, argv, &lifecycle_cb, (void *)&app);

  return ret;
}
