from django.shortcuts import render

# Create your views here.
from rest_framework.decorators import api_view
from rest_framework.response import Response
from .models import VibrationLog
from .serializers import VibrationLogSerializer

@api_view(['GET'])
def get_live_telemetry(request):
    logs = VibrationLog.objects.order_by('-timestamp')[:50]
    serializer = VibrationLogSerializer(logs, many=True)
    return Response(serializer.data)