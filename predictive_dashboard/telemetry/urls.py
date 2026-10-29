from django.urls import path
from . import views

urlpatterns = [
    path('live/', views.get_live_telemetry, name='live_telemetry'),
]