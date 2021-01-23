/*
 *  Copyright © 2017-2020 Wellington Wallace
 *
 *  This file is part of PulseEffects.
 *
 *  PulseEffects is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  PulseEffects is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with PulseEffects.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "util.hpp"

namespace util {

void debug(const std::string& s) {
  g_debug(s.c_str(), "%s");
}

void error(const std::string& s) {
  g_error(s.c_str(), "%s");
}

void critical(const std::string& s) {
  g_critical(s.c_str(), "%s");
}

void warning(const std::string& s) {
  g_warning(s.c_str(), "%s");
}

void info(const std::string& s) {
  g_info(s.c_str(), "%s");
}

void print_thread_id() {
  std::cout << "thread id: " << std::this_thread::get_id() << std::endl;
}

auto get_global_locale() -> std::locale {
  // set locale (workaround for #849)

  try {
    return std::locale("");
  } catch (const std::exception& e) {
    return std::locale();
  }
}

auto get_c_locale() -> std::locale {
  return std::locale();
}

auto logspace(const float& start, const float& stop, const uint& npoints) -> std::vector<float> {
  std::vector<float> output;

  if (stop <= start) {
    return output;
  }

  float delta = (stop - start) / npoints;

  float v = start;

  while (v <= stop) {
    output.emplace_back(powf(10.0F, v));

    v += delta;
  }

  return output;
}

auto linspace(const float& start, const float& stop, const uint& npoints) -> std::vector<float> {
  std::vector<float> output;

  if (stop <= start) {
    return output;
  }

  float delta = (stop - start) / npoints;

  float v = start;

  while (v <= stop) {
    output.emplace_back(v);

    v += delta;
  }

  return output;
}

auto db20_gain_to_linear(GValue* value, GVariant* variant, gpointer user_data) -> gboolean {
  double v_db = g_variant_get_double(variant);

  float v_linear = powf(10.0F, static_cast<float>(v_db) / 20.0F);

  g_value_set_float(value, v_linear);

  return 1;
}

auto linear_gain_to_db20(const GValue* value, const GVariantType* expected_type, gpointer user_data) -> GVariant* {
  float v_linear = g_value_get_float(value);

  double v_db = 20.0 * log10f(static_cast<double>(v_linear));

  return g_variant_new_double(v_db);
}

auto db10_gain_to_linear(GValue* value, GVariant* variant, gpointer user_data) -> gboolean {
  double v_db = g_variant_get_double(variant);

  float v_linear = powf(10.0F, static_cast<float>(v_db) / 10.0F);

  g_value_set_float(value, v_linear);

  return 1;
}

auto double_to_float(GValue* value, GVariant* variant, gpointer user_data) -> gboolean {
  float v_d = g_variant_get_double(variant);

  g_value_set_float(value, v_d);

  return 1;
}

auto db20_gain_to_linear_double(GValue* value, GVariant* variant, gpointer user_data) -> gboolean {
  double v_db = g_variant_get_double(variant);

  double v_linear = pow(10.0, v_db / 20.0);

  g_value_set_double(value, v_linear);

  return 1;
}

auto linear_double_gain_to_db20(const GValue* value, const GVariantType* expected_type, gpointer user_data)
    -> GVariant* {
  double v_linear = g_value_get_double(value);

  double v_db = 20.0 * log10(v_linear);

  return g_variant_new_double(v_db);
}

auto double_x10_to_int(GValue* value, GVariant* variant, gpointer user_data) -> gboolean {
  double v_d = g_variant_get_double(variant);

  g_value_set_int(value, v_d * 10);

  return 1;
}

auto ms_to_ns(GValue* value, GVariant* variant, gpointer user_data) -> gboolean {
  guint64 v_ns = g_variant_get_double(variant) * 1000000.0;

  g_value_set_uint64(value, v_ns);

  return 1;
}

}  // namespace util
