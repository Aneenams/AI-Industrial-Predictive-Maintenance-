from rest_framework import serializers
from .models import VibrationLog

class VibrationLogSerializer(serializers.ModelSerializer):
    class Meta:
        model = VibrationLog
        fields = '__all__'